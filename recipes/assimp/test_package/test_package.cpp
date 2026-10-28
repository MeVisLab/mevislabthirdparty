#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Need at least one argument" << std::endl;
        return 1;
    }

    Assimp::Importer importer;
    const aiScene *scene =
        importer.ReadFile(argv[1], aiProcess_CalcTangentSpace | aiProcess_Triangulate |
                                       aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

    if (!scene)
    {
        return 1;
    }

    return 0;
}
