#include <pcl/common/point_tests.h>
#include <pcl/point_types.h>
#include <pcl/surface/concave_hull.h>

#include <Eigen/Geometry>

#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

void testConcaveHullAlignmentReproducer()
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    constexpr double pi = 3.14159265358979323846;

    const Eigen::Vector3f center(0.4f, -1.2f, 2.5f);
    const Eigen::Vector3f u = Eigen::Vector3f(1.0f, 0.35f, -0.2f).normalized();
    const Eigen::Vector3f normal = Eigen::Vector3f(0.25f, -0.8f, 0.55f).normalized();
    const Eigen::Vector3f v = normal.cross(u).normalized();

    for (int i = 0; i < 48; ++i)
    {
        const double angle = 2.0 * pi * static_cast<double>(i) / 48.0;
        const float radius = (i % 7 == 0) ? 1.35f : 1.0f;
        const Eigen::Vector3f point = center + radius * static_cast<float>(std::cos(angle)) * u +
                                      radius * static_cast<float>(std::sin(angle)) * v;

        cloud->push_back(pcl::PointXYZ(point.x(), point.y(), point.z()));
    }

    cloud->width = static_cast<std::uint32_t>(cloud->size());
    cloud->height = 1;
    cloud->is_dense = true;

    pcl::ConcaveHull<pcl::PointXYZ> concave_hull;
    concave_hull.setInputCloud(cloud);
    concave_hull.setAlpha(0.75);

    pcl::PointCloud<pcl::PointXYZ> alpha_shape;
    std::vector<pcl::Vertices> polygons;
    concave_hull.reconstruct(alpha_shape, polygons);

    if (concave_hull.getDimension() != 2)
    {
        throw std::runtime_error("ConcaveHull did not use the planar reconstruction path");
    }

    if (alpha_shape.empty())
    {
        throw std::runtime_error("ConcaveHull returned no hull points");
    }

    if (polygons.empty())
    {
        throw std::runtime_error("ConcaveHull returned no polygons");
    }

    for (const auto &point : alpha_shape)
    {
        if (!pcl::isFinite(point))
        {
            throw std::runtime_error("ConcaveHull returned a non-finite hull point");
        }
    }
}


int main()
{
    pcl::PointXYZ p_valid;
    p_valid.x = 0;
    p_valid.y = 0;
    p_valid.z = 0;
    std::cout << "Is p_valid valid? " << pcl::isFinite(p_valid) << std::endl;

    // If any component is NaN, the point is not finite.
    pcl::PointXYZ p_invalid;
    p_invalid.x = std::numeric_limits<float>::quiet_NaN();
    p_invalid.y = 0;
    p_invalid.z = 0;
    std::cout << "Is p_invalid valid? " << pcl::isFinite(p_invalid) << std::endl;

    testConcaveHullAlignmentReproducer();
    std::cout << "ConcaveHull alignment passed" << std::endl;

    return 0;
}
