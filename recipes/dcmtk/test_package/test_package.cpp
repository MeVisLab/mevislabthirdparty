#include "dcmtk/dcmdata/dcddirif.h"
#include "dcmtk/dcmdata/dcuid.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/oflog/oflog.h"
#include "dcmtk/dcmsr/dsrdoc.h"

#include <iostream>

int main(int argc, char *argv[])
{
    if(argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <dcmfile>" << std::endl;
        return 1;
    }

    std::cout << "DCMTK version " << OFFIS_DCMTK_VERSION << std::endl;

    char uid[65];
    dcmGenerateUniqueIdentifier(uid, "myprefix_");

    {
        DcmFileFormat fileformat;
        DcmDataset *dataset = fileformat.getDataset();
        dataset->putAndInsertString(DCM_SOPClassUID, UID_SecondaryCaptureImageStorage);
        dataset->putAndInsertString(DCM_SOPInstanceUID, uid);
        dataset->putAndInsertString(DCM_PatientName, "Doe^John");
        if(auto status = fileformat.saveFile("generated_test_file.dcm", EXS_LittleEndianExplicit); status.bad()) {
            std::cerr << "ERROR: cannot write DICOM file (" << status.text() << ")" << std::endl;
            return 1;
        }
    }

    {
        DcmFileFormat fileformat;
        if(auto status = fileformat.loadFile("generated_test_file.dcm"); status.bad()) {
            std::cerr << "ERROR: cannot read DICOM file (" << status.text() << ")" << std::endl;
            return 1;
        }

        auto dataset = fileformat.getDataset();
        if(auto status = dataset->convertToUTF8(); status.bad()) {
            std::cerr << "ERROR: failed to convert dataset (" << status.text() << ")" << std::endl;
            return 1;
        }

        OFString sopInstanceUID;
        if (dataset->findAndGetOFString(DCM_SOPInstanceUID, sopInstanceUID).bad()) {
            std::cerr << "ERROR: cannot access DCM_SOPInstanceUID!" << std::endl;
            return 1;
        }

        if(sopInstanceUID.compare(uid) != 0) {
            std::cerr << "ERROR: wrong sopInstanceUID!" << std::endl;
            return 1;
        }

        OFString patientName;
        if (dataset->findAndGetOFString(DCM_PatientName, patientName).bad()) {
            std::cerr << "ERROR: cannot access DCM_PatientName!" << std::endl;
            return 1;
        }

        if(patientName.compare("Doe^John") != 0) {
            std::cerr << "ERROR: wrong patientName!" << std::endl;
            return 1;
        }
    }

    {
        DcmFileFormat fileformat;
        if(auto status = fileformat.loadFile(argv[1]); status.bad()) {
            std::cerr << "ERROR: cannot read DICOM file " << argv[1] << " (" << status.text() << ")" << std::endl;
            return 1;
        }

        auto dataset = fileformat.getDataset();
        if(auto status = dataset->convertToUTF8(); status.bad()) {
            std::cerr << "ERROR: failed to convert dataset (" << status.text() << ")" << std::endl;
            return 1;
        }

        OFString sopInstanceUID;
        if (dataset->findAndGetOFString(DCM_SOPInstanceUID, sopInstanceUID).bad()) {
            std::cerr << "ERROR: cannot access DCM_SOPInstanceUID!" << std::endl;
            return 1;
        }

        if(sopInstanceUID.compare("1.2.276.0.28.3.233845177365477.42.576.20140122150447000") != 0) {
            std::cerr << "ERROR: wrong sopInstanceUID!" << std::endl;
            return 1;
        }

        OFString patientName;
        if (dataset->findAndGetOFString(DCM_PatientName, patientName).bad()) {
            std::cerr << "ERROR: cannot access DCM_PatientName!" << std::endl;
            return 1;
        }

        if(patientName.compare("Yamada^Tarou=山田^太郎=やまだ^たろう") != 0) {
            std::cerr << "ERROR: wrong patientName!" << std::endl;
            return 1;
        }
    }

    return 0;
}
