#include "step2.hpp"

#include <stdlib.h>

#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "ship.hpp"

int main(int argc, char * argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: programName shipFile cargoFile" << std::endl;
    exit(EXIT_FAILURE);
  }

  // read ship
  std::ifstream f(argv[1]);
  if (!f) {
    std::cerr << "Failed to open the file " << argv[1] << std::endl;
    exit(EXIT_FAILURE);
  }
  // name in aphabetic order
  std::vector<Container> containerList;
  // name in input order
  std::vector<std::string> containerNameList;
  readShipData(f, containerList, containerNameList);
  f.close();
  // cargo
  std::ifstream f2(argv[2]);
  if (!f2) {
    std::cerr << "Failed to open the file " << argv[2] << std::endl;
    exit(EXIT_FAILURE);
  }
  readLoadCargo(f2, containerList);
  f2.close();
  // print in the order in input file
  printCargo(containerList, containerNameList);
  return 0;
}
