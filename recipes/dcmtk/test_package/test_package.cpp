#include "dcmtk/dcmdata/dccodec.h"
#include "dcmtk/dcmdata/dcddirif.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmdata/dcuid.h"
#include "dcmtk/dcmimgle/dcmimage.h"
#include "dcmtk/dcmjpeg/djdecode.h"
#include "dcmtk/dcmjpeg/djencode.h"
#include "dcmtk/dcmnet/assoc.h"
#include "dcmtk/dcmsr/dsrdoc.h"
#include "dcmtk/oflog/oflog.h"

#include <iostream>
#include <vector>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <dcmfile>" << std::endl;
        return 1;
    }

    std::cout << "DCMTK version " << OFFIS_DCMTK_VERSION << std::endl;

    char uid[65];
    dcmGenerateUniqueIdentifier(uid, "myprefix_");

    {
        DcmFileFormat fileformat;
        DcmDataset *dataset = fileformat.getDataset();
        if (auto status =
                dataset->putAndInsertString(DCM_SOPClassUID, UID_SecondaryCaptureImageStorage);
            status.bad())
        {
            std::cerr << "ERROR: cannot add element DCM_SOPClassUID (" << status.text() << ")"
                      << std::endl;
            return 1;
        }

        if (auto status = dataset->putAndInsertString(DCM_SOPInstanceUID, uid); status.bad())
        {
            std::cerr << "ERROR: cannot add element DCM_SOPInstanceUID (" << status.text() << ")"
                      << std::endl;
            return 1;
        }

        if (auto status = dataset->putAndInsertString(DCM_PatientName, "Doe^John"); status.bad())
        {
            std::cerr << "ERROR: cannot add element DCM_PatientName (" << status.text() << ")"
                      << std::endl;
            return 1;
        }

        if (auto status = fileformat.saveFile("generated_test_file.dcm", EXS_LittleEndianExplicit);
            status.bad())
        {
            std::cerr << "ERROR: cannot write DICOM file (" << status.text() << ")" << std::endl;
            return 1;
        }
    }

    {
        DcmFileFormat fileformat;
        if (auto status = fileformat.loadFile("generated_test_file.dcm"); status.bad())
        {
            std::cerr << "ERROR: cannot read DICOM file (" << status.text() << ")" << std::endl;
            return 1;
        }

        auto dataset = fileformat.getDataset();
        if (auto status = dataset->convertToUTF8(); status.bad())
        {
            std::cerr << "ERROR: failed to convert dataset (" << status.text() << ")" << std::endl;
            return 1;
        }

        OFString sopInstanceUID;
        if (dataset->findAndGetOFString(DCM_SOPInstanceUID, sopInstanceUID).bad())
        {
            std::cerr << "ERROR: cannot access DCM_SOPInstanceUID!" << std::endl;
            return 1;
        }

        if (sopInstanceUID.compare(uid) != 0)
        {
            std::cerr << "ERROR: wrong sopInstanceUID!" << std::endl;
            return 1;
        }

        OFString patientName;
        if (dataset->findAndGetOFString(DCM_PatientName, patientName).bad())
        {
            std::cerr << "ERROR: cannot access DCM_PatientName!" << std::endl;
            return 1;
        }

        if (patientName.compare("Doe^John") != 0)
        {
            std::cerr << "ERROR: wrong patientName!" << std::endl;
            return 1;
        }
    }

    {
        DcmFileFormat fileformat;
        if (auto status = fileformat.loadFile(argv[1]); status.bad())
        {
            std::cerr << "ERROR: cannot read DICOM file " << argv[1] << " (" << status.text() << ")"
                      << std::endl;
            return 1;
        }

        auto dataset = fileformat.getDataset();
        if (auto status = dataset->convertToUTF8(); status.bad())
        {
            std::cerr << "ERROR: failed to convert dataset (" << status.text() << ")" << std::endl;
            return 1;
        }

        OFString sopInstanceUID;
        if (dataset->findAndGetOFString(DCM_SOPInstanceUID, sopInstanceUID).bad())
        {
            std::cerr << "ERROR: cannot access DCM_SOPInstanceUID!" << std::endl;
            return 1;
        }

        if (sopInstanceUID.compare("1.2.276.0.28.3.233845177365477.42.576.20140122150447000") != 0)
        {
            std::cerr << "ERROR: wrong sopInstanceUID!" << std::endl;
            return 1;
        }

        OFString patientName;
        if (dataset->findAndGetOFString(DCM_PatientName, patientName).bad())
        {
            std::cerr << "ERROR: cannot access DCM_PatientName!" << std::endl;
            return 1;
        }

        if (patientName.compare("Yamada^Tarou=山田^太郎=やまだ^たろう") != 0)
        {
            std::cerr << "ERROR: wrong patientName!" << std::endl;
            return 1;
        }
    }

    {
        const Uint16 width = 16;
        const Uint16 height = 8;
        DcmDataset dataset;
        dataset.putAndInsertString(DCM_SOPClassUID, UID_SecondaryCaptureImageStorage);
        dataset.putAndInsertString(DCM_PhotometricInterpretation, "MONOCHROME2");
        dataset.putAndInsertUint16(DCM_SamplesPerPixel, 1);
        dataset.putAndInsertUint16(DCM_Rows, height);
        dataset.putAndInsertUint16(DCM_Columns, width);
        dataset.putAndInsertUint16(DCM_BitsAllocated, 8);
        dataset.putAndInsertUint16(DCM_BitsStored, 8);
        dataset.putAndInsertUint16(DCM_HighBit, 7);
        dataset.putAndInsertUint16(DCM_PixelRepresentation, 0);
        std::vector<Uint8> pixels(width * height);
        for (size_t i = 0; i < pixels.size(); ++i)
        {
            pixels[i] = static_cast<Uint8>(i);
        }
        if (auto status = dataset.putAndInsertUint8Array(DCM_PixelData, pixels.data(),
                                                         static_cast<unsigned long>(pixels.size()));
            status.bad())
        {
            std::cerr << "ERROR: cannot insert pixel data (" << status.text() << ")" << std::endl;
            return 1;
        }

        DicomImage image(&dataset, EXS_LittleEndianExplicit);
        if (image.getStatus() != EIS_Normal || image.getWidth() != width ||
            image.getHeight() != height)
        {
            std::cerr << "ERROR: DicomImage failed (" << DicomImage::getString(image.getStatus())
                      << ")" << std::endl;
            return 1;
        }
    }

    {
        DJDecoderRegistration::registerCodecs();
        DJEncoderRegistration::registerCodecs();
        const OFBool canDecode =
            DcmCodecList::canChangeCoding(EXS_JPEGProcess14SV1, EXS_LittleEndianExplicit);
        const OFBool canEncode =
            DcmCodecList::canChangeCoding(EXS_LittleEndianExplicit, EXS_JPEGProcess14SV1);
        DJEncoderRegistration::cleanup();
        DJDecoderRegistration::cleanup();
        if (!canDecode || !canEncode)
        {
            std::cerr << "ERROR: JPEG codecs are not registered" << std::endl;
            return 1;
        }
    }

    {
        DSRDocument document(DSRTypes::DT_BasicTextSR);
        document.createNewDocument();
        DSRDocumentTree &tree = document.getTree();
        if (tree.addContentItem(DSRTypes::RT_isRoot, DSRTypes::VT_Container) == 0 ||
            tree.addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Text,
                                DSRTypes::AM_belowCurrent) == 0 ||
            tree.getCurrentContentItem().setStringValue("Hello DCMTK").bad() ||
            tree.countNodes() != 2)
        {
            std::cerr << "ERROR: cannot build SR document tree" << std::endl;
            return 1;
        }
    }

    {
        T_ASC_Network *network = nullptr;
        if (auto status = ASC_initializeNetwork(NET_REQUESTOR, 0, 30, &network); status.bad())
        {
            std::cerr << "ERROR: cannot initialize network (" << status.text() << ")" << std::endl;
            return 1;
        }
        if (auto status = ASC_dropNetwork(&network); status.bad())
        {
            std::cerr << "ERROR: cannot drop network (" << status.text() << ")" << std::endl;
            return 1;
        }
    }

    return 0;
}
