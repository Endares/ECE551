#include "step1.hpp"

#include <stdlib.h>

#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

int main(int argc, char * argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: programName inputFileName\n" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::ifstream f(argv[1]);
  if (!f) {
    std::cerr << "Failed to open the file " << argv[1] << std::endl;
    exit(EXIT_FAILURE);
  }
  std::map<std::string, uint64_t> routeInfo;
  readRouteData(f, routeInfo);
  f.close();
  printRouteInfo(routeInfo);

  return 0;
}
