#include <stdlib.h>

#include <climits>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "ship1.hpp"

Ship * makeShip(std::vector<std::string> & line) {
  /* ship type (reside in line[1]):
     Container, Tanker, Animals*/
  std::string temp;
  std::vector<std::string> typeInfo;
  std::istringstream iss(line[1]);
  while (getline(iss, temp, ',')) {
    typeInfo.push_back(temp);
  }
  if (typeInfo.size() < 2) {
    std::cerr << "Missing fields in typeInfo." << std::endl;
    exit(EXIT_FAILURE);
  }
  Ship * sh;
  if (typeInfo[0] == "Container") {
    sh = new Container(line[0], line[2], line[3], stoull(line[4]), stoull(typeInfo[1]));
    for (size_t i = 2; i < typeInfo.size(); ++i) {
      sh->addProperty(typeInfo[i]);
    }
  }
  else if (typeInfo[0] == "Tanker") {
    if (typeInfo.size() < 4) {
      std::cerr << "Missing fields in tanker typeInfo." << std::endl;
      exit(EXIT_FAILURE);
    }
    // Error if capacity is not a multiple of the number of tanks.
    if (stoull(typeInfo[3]) == 0 || stoull(line[4]) % stoull(typeInfo[3]) != 0) {
      std::cerr << "Capacity is not divisible by tankNum." << std::endl;
      exit(EXIT_FAILURE);
    }
    sh = new Tanker(line[0],
                    line[2],
                    line[3],
                    stoull(line[4]),
                    stoull(typeInfo[3]),
                    stoll(typeInfo[1]),
                    stoll(typeInfo[2]));
    for (size_t i = 4; i < typeInfo.size(); ++i) {
      sh->addProperty(typeInfo[i]);
    }
  }
  else if (typeInfo[0] == "Animals") {
    sh = new AnimalShip(line[0], line[2], line[3], stoull(line[4]), stoull(typeInfo[1]));
  }
  else {
    std::cerr << "Invalid ship type:" << typeInfo[0] << std::endl;
    exit(EXIT_FAILURE);
  }
  return sh;
}

/* read ship data from istream is, store data in:
   1. vector<Ship*> shipList, as the input order 
   2. map<shipName, Ship*> sortedShipList, as name's alphabetic order
      use shallow copy here.
*/
void readShipFile(std::istream & is, std::vector<Ship *> & shipList) {
  std::string curr;
  // make sure no duplication in ship's names
  std::unordered_set<std::string> nameSet;

  // read in one line per time, split fields with ':'
  while (getline(is, curr)) {
    std::string temp;
    std::vector<std::string> line;
    std::istringstream iss(curr);
    while (getline(iss, temp, ':')) {
      line.push_back(temp);
    }
    // every ship must have 5 fields
    if (line.size() != 5) {
      std::cerr << "Invalid input, wrong number of fields.\n" << std::endl;
      exit(EXIT_FAILURE);
    }
    Ship * sh;
    // duplicated ship name is not legal
    if (nameSet.count(line[0])) {
      std::cerr << "Duplicated ship name." << std::endl;
      exit(EXIT_FAILURE);
    }
    else {
      sh = makeShip(line);
      nameSet.insert(line[0]);
    }
    shipList.push_back(sh);
  }
}

void printCapableList(Cargo * c, std::map<std::string, Ship *> & capableList) {
  if (capableList.size() == 0) {
    std::cout << "No ships can carry the " << c->getName() << " from " << c->getSrc()
              << " to " << c->getDest() << std::endl;
  }
  else {
    std::cout << capableList.size() << " ships can carry the " << c->getName() << " from "
              << c->getSrc() << " to " << c->getDest() << std::endl;
    for (auto & p : capableList) {
      std::cout << "  " << p.second->getName() << std::endl;
    }
  }
}

// load Cargo c onto Container con
void loadCargo(Ship * sh, Cargo * c) {
  std::cout << "  **Loading the cargo onto " << sh->getName() << "**" << std::endl;
  sh->addCargo(c);
}

/* Handle each cargo: spcify which ships it can load onto */
void handleCargo(Cargo * ca, std::vector<Ship *> shipList) {
  // sorted by name's alphabetic order
  std::map<std::string, Ship *> capableList;
  for (Ship * sh : shipList) {
    if (sh->canAdd(ca)) {
      capableList[sh->getName()] = sh;
    }
  }
  printCapableList(ca, capableList);
  // load onto the first ship in the list
  if (!capableList.empty()) {
    loadCargo(capableList.begin()->second, ca);
  }
}

/* Make a cargo according to input data */
Cargo * makeCargo(std::vector<std::string> info, std::string & type) {
  Cargo * ca = new Cargo(info[0], info[1], info[2], stoull(info[3]), type);
  // temperature. only useful for liquid or gas
  int min = INT_MIN;
  int max = INT_MAX;

  for (size_t i = 4; i < info.size(); ++i) {
    // check property prefix and delete prefix
    // hazardous
    if (info[i].find("hazardous-") == 0) {
      ca->addProperty(info[i].substr(10));  // start from index = 10
    }

    // temperature
    else if (info[i].find("maxtemp=") == 0) {
      max = stoll(info[i].substr(8));
    }
    else if (info[i].find("maxtemp") == 0) {
      max = 0;
    }
    else if (info[i].find("mintemp=") == 0) {
      min = stoll(info[i].substr(8));
    }
    else if (info[i].find("mintemp") == 0) {
      min = 0;
    }
  }
  ca->setTempRange(min, max);
  return ca;
}

/* Read cargo from istream is, store in cargoList */
void readCargo(std::istream & is, std::vector<Cargo *> & cargoList) {
  std::string curr;
  while (getline(is, curr)) {
    std::string temp;
    std::vector<std::string> line;
    std::istringstream iss(curr);

    /* cargo type:
       invalid, container, liquid, gas, animal, roamer */
    std::string type = "invalid";
    while (getline(iss, temp, ',')) {
      if (temp == "container") {
        type = "container";
      }
      else if (temp == "liquid") {
        type = "liquid";
      }
      else if (temp == "gas") {
        type = "gas";
      }
      else if (temp == "animal") {
        if (type != "roamer")
          type = "animal";
      }
      else if (temp == "roamer") {
        type = "roamer";
      }
      else {
        line.push_back(temp);
      }
    }
    if (type == "invalid") {
      std::cerr << "Invalid cargo type." << std::endl;
      exit(EXIT_FAILURE);
    }
    Cargo * ca = makeCargo(line, type);
    cargoList.push_back(ca);
  }
}

/* print all ship's cargo in the order as input file */
void printCargo(std::vector<Ship *> & shipList) {
  // print status of each container after all cargoes are loaded
  std::cout << "---Done Loading---Here are the ships---" << std::endl;
  for (Ship * sh : shipList) {
    sh->printStatus();
  }
}
