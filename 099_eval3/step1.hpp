#include <stdlib.h>

#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

void readRouteData(std::istream & is, std::map<std::string, uint64_t> & routeInfo) {
  std::set<std::string> nameSet;
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
    if (nameSet.count(line[0])) {
      std::cerr << "Duplicated ship name!" << std::endl;
      exit(EXIT_FAILURE);
    }
    else {
      nameSet.insert(line[0]);
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
