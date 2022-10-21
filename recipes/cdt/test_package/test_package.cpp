#include <iostream>
#include <CDT/CDT.h>
#include <utility>
#include <vector>

int main()
{
  std::vector<std::pair<double, double>> vertices = {{100, 0}, {100, 100}, {0, 100}, {0, 0}};
  std::vector<std::pair<unsigned, unsigned>> edges{{0,1}, {1, 2}, {2, 3}, {3, 0}};

  auto cdt = CDT::Triangulation<double>(CDT::VertexInsertionOrder::AsProvided);

  cdt.insertVertices(vertices.begin(), vertices.end(), [](const auto& v) { return v.first; }, [](const auto& v) { return v.second; });
  cdt.insertEdges(edges.begin(), edges.end(), [](const auto& e) { return e.first; }, [](const auto& e) { return e.second; });
  cdt.eraseOuterTrianglesAndHoles();

  for (const auto& triangle : cdt.triangles)
  {
    std::cout << "(" << triangle.vertices[0] << "," << triangle.vertices[1] << "," << triangle.vertices[2] << ")" << std::endl;
  }

  return 0;
}
