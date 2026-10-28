#include <embree4/rtcore.h>
#include <embree4/rtcore_ray.h>

#include <cmath>
#include <iostream>

int main()
{
    RTCDevice device = rtcNewDevice(nullptr);
    if (!device)
    {
        std::cerr << "rtcNewDevice failed" << std::endl;
        return 1;
    }

    RTCScene scene = rtcNewScene(device);
    RTCGeometry geometry = rtcNewGeometry(device, RTC_GEOMETRY_TYPE_TRIANGLE);
    float *vertices = static_cast<float *>(rtcSetNewGeometryBuffer(
        geometry, RTC_BUFFER_TYPE_VERTEX, 0, RTC_FORMAT_FLOAT3, 3 * sizeof(float), 3));
    unsigned *indices = static_cast<unsigned *>(rtcSetNewGeometryBuffer(
        geometry, RTC_BUFFER_TYPE_INDEX, 0, RTC_FORMAT_UINT3, 3 * sizeof(unsigned), 1));
    const float triangle[9] = {-1.f, -1.f, 5.f, 1.f, -1.f, 5.f, 0.f, 1.f, 5.f};
    for (int i = 0; i < 9; ++i)
    {
        vertices[i] = triangle[i];
    }
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    rtcCommitGeometry(geometry);
    const unsigned geometry_id = rtcAttachGeometry(scene, geometry);
    rtcReleaseGeometry(geometry);
    rtcCommitScene(scene);

    RTCRayHit rayhit;
    rayhit.ray.org_x = 0.f;
    rayhit.ray.org_y = 0.f;
    rayhit.ray.org_z = 0.f;
    rayhit.ray.dir_x = 0.f;
    rayhit.ray.dir_y = 0.f;
    rayhit.ray.dir_z = 1.f;
    rayhit.ray.tnear = 0.f;
    rayhit.ray.tfar = 100.f;
    rayhit.ray.mask = static_cast<unsigned>(-1);
    rayhit.ray.flags = 0;
    rayhit.ray.time = 0.f;
    rayhit.hit.geomID = RTC_INVALID_GEOMETRY_ID;
    rayhit.hit.instID[0] = RTC_INVALID_GEOMETRY_ID;
    rtcIntersect1(scene, &rayhit, nullptr);

    int result = 0;
    if (rayhit.hit.geomID != geometry_id || rayhit.hit.primID != 0 ||
        std::fabs(rayhit.ray.tfar - 5.f) > 1e-4f)
    {
        std::cerr << "unexpected hit: geomID=" << rayhit.hit.geomID
                  << " primID=" << rayhit.hit.primID << " tfar=" << rayhit.ray.tfar << std::endl;
        result = 1;
    }
    else
    {
        std::cout << "hit triangle at distance " << rayhit.ray.tfar << std::endl;
    }

    rtcReleaseScene(scene);
    rtcReleaseDevice(device);
    return result;
}
