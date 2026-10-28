#include <iostream>
#include <vtkImageData.h>
#include <vtkImageGaussianSmooth.h>
#include <vtkLine.h>
#include <vtkNew.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkXMLPolyDataWriter.h>

#ifdef WITH_RENDERING
#include <vtkActor.h>
#include <vtkAutoInit.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
#endif

int main()
{
    double lineP0[3] = {0.0, 0.0, 0.0};
    double lineP1[3] = {2.0, 0.0, 0.0};

    double p0[3] = {1.0, 0, 0};
    double p1[3] = {1.0, 2.0, 0};

    {
        double dist0 = vtkLine::DistanceToLine(p0, lineP0, lineP1);
        std::cout << "Dist0: " << dist0 << std::endl;

        double dist1 = vtkLine::DistanceToLine(p1, lineP0, lineP1);
        std::cout << "Dist1: " << dist1 << std::endl;
    }

    {
        double t;
        double closest[3];
        double dist0 = vtkLine::DistanceToLine(p0, lineP0, lineP1, t, closest);
        std::cout << "Dist0: " << dist0 << " closest point: " << closest[0] << " " << closest[1]
                  << " " << closest[2] << std::endl;

        double dist1 = vtkLine::DistanceToLine(p1, lineP0, lineP1, t, closest);
        std::cout << "Dist1: " << dist1 << " closest point: " << closest[0] << " " << closest[1]
                  << " " << closest[2] << std::endl;
    }

    vtkNew<vtkSphereSource> sphere;
    sphere->SetThetaResolution(8);
    sphere->SetPhiResolution(8);
    sphere->Update();
    const vtkIdType pointCount = sphere->GetOutput()->GetNumberOfPoints();
    if (pointCount <= 0)
    {
        std::cerr << "sphere source produced no points" << std::endl;
        return 1;
    }

#ifdef WITH_RENDERING
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    if (!mapper)
    {
        std::cerr << "no vtkPolyDataMapper implementation available" << std::endl;
        return 1;
    }
    mapper->SetInputConnection(sphere->GetOutputPort());
    mapper->Update();
    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);
    vtkNew<vtkRenderer> renderer;
    renderer->AddActor(actor);
    if (renderer->GetActors()->GetNumberOfItems() != 1)
    {
        std::cerr << "renderer does not hold the added actor" << std::endl;
        return 1;
    }
#endif

    vtkNew<vtkImageData> image;
    image->SetDimensions(16, 16, 1);
    image->AllocateScalars(VTK_FLOAT, 1);
    for (int y = 0; y < 16; ++y)
    {
        for (int x = 0; x < 16; ++x)
        {
            *static_cast<float *>(image->GetScalarPointer(x, y, 0)) =
                (x == 8 && y == 8) ? 1.0f : 0.0f;
        }
    }
    vtkNew<vtkImageGaussianSmooth> smooth;
    smooth->SetInputData(image);
    smooth->SetDimensionality(2);
    smooth->Update();
    const float center = smooth->GetOutput()->GetScalarComponentAsFloat(8, 8, 0, 0);
    const float neighbor = smooth->GetOutput()->GetScalarComponentAsFloat(9, 8, 0, 0);
    if (!(center > neighbor && neighbor > 0.0f && center < 1.0f))
    {
        std::cerr << "gaussian smooth produced unexpected values" << std::endl;
        return 1;
    }

    vtkNew<vtkXMLPolyDataWriter> writer;
    writer->SetFileName("sphere.vtp");
    writer->SetInputConnection(sphere->GetOutputPort());
    if (!writer->Write())
    {
        std::cerr << "failed to write sphere.vtp" << std::endl;
        return 1;
    }
    vtkNew<vtkXMLPolyDataReader> reader;
    reader->SetFileName("sphere.vtp");
    reader->Update();
    if (reader->GetOutput()->GetNumberOfPoints() != pointCount)
    {
        std::cerr << "XML poly data round trip lost points" << std::endl;
        return 1;
    }

    return 0;
}
