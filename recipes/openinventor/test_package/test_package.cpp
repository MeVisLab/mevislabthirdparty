#include <Inventor/SbViewportRegion.h>
#include <Inventor/SoDB.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/actions/SoSearchAction.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTransform.h>

#include <cmath>
#include <cstdio>

int main()
{
    SoDB::init();

    SoSeparator *root = new SoSeparator;
    root->ref();
    SoTransform *transform = new SoTransform;
    transform->translation.setValue(10.0f, 0.0f, 0.0f);
    transform->scaleFactor.setValue(2.0f, 2.0f, 2.0f);
    root->addChild(transform);
    SoCube *cube = new SoCube;
    root->addChild(cube);

    SoGetBoundingBoxAction boundingBoxAction(SbViewportRegion(100, 100));
    boundingBoxAction.apply(root);
    const SbBox3f box = boundingBoxAction.getBoundingBox();
    float sizeX = 0.0f, sizeY = 0.0f, sizeZ = 0.0f;
    box.getSize(sizeX, sizeY, sizeZ);
    const SbVec3f center = box.getCenter();
    if (std::fabs(sizeX - 4.0f) > 1e-4f || std::fabs(sizeY - 4.0f) > 1e-4f ||
        std::fabs(sizeZ - 4.0f) > 1e-4f || std::fabs(center[0] - 10.0f) > 1e-4f)
    {
        fprintf(stderr, "unexpected bounding box: size %f %f %f, center %f %f %f\n", sizeX, sizeY,
                sizeZ, center[0], center[1], center[2]);
        return 1;
    }

    SoSearchAction searchAction;
    searchAction.setType(SoCube::getClassTypeId());
    searchAction.apply(root);
    if (!searchAction.getPath() || searchAction.getPath()->getTail() != cube)
    {
        fprintf(stderr, "search action did not find the cube\n");
        return 1;
    }

    root->unref();
    return 0;
}
