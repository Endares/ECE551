#include <stdlib.h>

#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

//#include "ship.hpp"

void readShipData(std::istream & is, std::map<std::string, uint64_t> & routeInfo) {
  std::string curr;
  while (getline(is, curr)) {
    std::string temp;
    std::vector<std::string> line;
    std::istringstream iss(curr);
    while (getline(iss, temp, ':')) {
      line.push_back(temp);
    }
    if (line.size() != 5) {
      std::cerr << "Invalid input, wrong number of fields.\n" << std::endl;
      exit(EXIT_FAILURE);
    }
    std::string route = line[2] + "->" + line[3];
    routeInfo[route] += std::stoull(line[4]);
  }
}

void printRouteInfo(std::map<std::string, uint64_t> & routeInfo) {
  std::map<std::string, uint64_t>::const_iterator it;
  for (it = routeInfo.begin(); it != routeInfo.end(); ++it) {
    std::cout << "(" << it->first << ") has total capacity " << it->second << std::endl;
  }
}

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
  readShipData(f, routeInfo);
  f.close();
  printRouteInfo(routeInfo);

  return 0;
}
