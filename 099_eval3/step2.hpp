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
void makeContainer(std::vector<std::string> & line, Container & c);
void readShipData(std::istream & is, std::vector<Container> & containerList) {
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
    /*    Container c;
    makeContainer(line, c);
    containerList.push_back(c);
    */
    containerList.emplace_back();
    makeContainer(line, containerList.back());
  }
}

// make a container from read data
void makeContainer(std::vector<std::string> & line, Container & c) {
  // extract type info of the ship
  std::istringstream iss(line[1]);
  std::string temp;
  std::vector<std::string> typeInfo;
  while (getline(iss, temp, ',')) {
    typeInfo.push_back(temp);
  }
  // should at least have ship type and slot number
  if (typeInfo.size() < 2) {
    std::cerr << "Invalid input: missing info of the ship's type." << std::endl;
    exit(EXIT_FAILURE);
  }
  if (typeInfo[0] != "Container") {
    std::cerr << "Not a container type!" << std::endl;
    exit(EXIT_FAILURE);
  }
  size_t slotNum = stoull(typeInfo[1]);
  std::unordered_set<std::string> hazmat;
  // hazmat info
  for (size_t i = 2; i < typeInfo.size(); ++i) {
    hazmat.insert(typeInfo[i]);
  }
  c.setContainer(line[0], line[2], line[3], stoull(line[4]), slotNum, hazmat);
}

void printCapableList(std::vector<Container *> & capableList, Cargo & c) {
  if (capableList.size() == 0) {
    std::cout << "No ships can carry the " << c.getName() << " from " << c.getSrc()
              << " to " << c.getDest() << std::endl;
  }
  else {
    std::cout << capableList.size() << " ships can carry the " << c.getName() << " from "
              << c.getSrc() << " to " << c.getDest() << std::endl;
    for (Container * con : capableList) {
      std::cout << "  " << con->getName() << std::endl;
    }
  }
}

// load Cargo c onto Container con
void loadCargo(Container & con, Cargo & c) {
  std::cout << "**Loading the cargo onto " << con.getName() << "**." << std::endl;
  con.addCargo(c);
}

/* make a cargo object, print the capable ships, and load the cargo onto the first capable one.*/
void handleCargo(std::vector<Container> & containerList, std::vector<std::string> line) {
  std::vector<std::string> hazmat;
  for (size_t i = 5; i < line.size(); ++i) {
    std::string s = line[i];
    // check property prefix and delete prefix
    if (s.find("hazardous-") == 0) {
      s = s.substr(10);  // start from index = 10
    }
    else {
      std::cerr << "Invalid property: missing prefix 'hazardous-'." << std::endl;
    }
    hazmat.push_back(s);
  }
  Cargo curr = Cargo(line[0], line[1], line[2], stoull(line[3]), line[4], hazmat);

  std::vector<Container *> capableList;
  for (Container & c : containerList) {
    if (c.canAdd(curr)) {
      capableList.push_back(&c);
    }
  }
  printCapableList(capableList, curr);
  if (capableList.size() != 0) {
    loadCargo(*capableList[0], curr);
  }
}

void readPrintLoadCargo(std::istream & is, std::vector<Container> & containerList) {
  std::string curr;
  while (getline(is, curr)) {
    std::string temp;
    std::vector<std::string> line;
    std::istringstream iss(curr);
    while (getline(iss, temp, ',')) {
      line.push_back(temp);
    }
    if (line.size() < 5) {
      std::cerr << "Invalid input: too few fields in the cargo." << std::endl;
      exit(EXIT_FAILURE);
    }
    if (line[4] == "container") {
      handleCargo(containerList, line);
    }
  }
  // print status of each container after all cargoes are loaded
  std::cout << "---Done Loading---Here are the ships---" << std::endl;
  for (Container & con : containerList) {
    con.printStatus();
  }
}
