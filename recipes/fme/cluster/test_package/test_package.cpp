#include <clHierarchicalClustering.h>
#include <clMetricFunctions.h>
#include <clPartitioningClustering.h>
#include <clRandom.h>
#include <clSOM.h>
#include <clSVD.h>

#include <cmath>
#include <cstdlib>
#include <iostream>

int main()
{
    double row0[2] = {0.0, 0.0};
    double row1[2] = {0.0, 1.0};
    double row2[2] = {10.0, 10.0};
    double row3[2] = {10.0, 12.0};
    double *data[4] = {row0, row1, row2, row3};
    double weight[2] = {1.0, 1.0};

    const double distance = euclid(2, data, data, weight, 2, 3, 0);
    if (std::fabs(distance - 2.0) > 1e-9)
    {
        std::cerr << "unexpected euclidean distance " << distance << std::endl;
        return 1;
    }

    double **distances = distancematrix(4, 2, data, weight, 'e', 0);
    if (distances == nullptr || std::fabs(distances[1][0] - 0.5) > 1e-9 ||
        std::fabs(distances[3][2] - 2.0) > 1e-9)
    {
        std::cerr << "unexpected distance matrix" << std::endl;
        return 1;
    }

    int clusterid[4] = {0, 0, 0, 0};
    double error = 0.0;
    int ifound = 0;
    cluster::kmedoids(2, 4, distances, 10, clusterid, &error, &ifound);
    for (int i = 1; i < 4; ++i)
    {
        free(distances[i]);
    }
    free(distances);
    if (ifound < 1 || clusterid[0] != clusterid[1] || clusterid[2] != clusterid[3] ||
        clusterid[0] == clusterid[2])
    {
        std::cerr << "unexpected clustering: " << clusterid[0] << clusterid[1] << clusterid[2]
                  << clusterid[3] << " (found " << ifound << " times)" << std::endl;
        return 1;
    }
    std::cout << "k-medoids separated the two groups with error " << error << std::endl;
    return 0;
}
