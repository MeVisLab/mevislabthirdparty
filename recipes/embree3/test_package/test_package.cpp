#include <embree3/rtcore.h>
#include <cstdlib>
#include <iostream>

int main() {
  std::cout << "Creating a new Embree device ..." << std::endl;
  auto device = rtcNewDevice("verbose=1");
  std::cout << "Releasing the Embree device ..." << std::endl;
  rtcReleaseDevice(device);
  std::cout << "'Embree package works!" << std::endl;
  return EXIT_SUCCESS;
}
