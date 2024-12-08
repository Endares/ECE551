#include "step4.hpp"

#include <stdlib.h>

#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "avl11.hpp"
#include "ship1.hpp"

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
  // Ship* in input order
  std::vector<Ship *> shipList;
  readShipFile(f, shipList);
  f.close();
  // Ship* in remaining-capacity ascending order, tie broken by name's alphabetic order
  std::map<std::string, AVLMultiMap<uint64_t, Ship *, compareByRemain, nameOrder> >
      shipRouteMap;
  makeAVLMap(shipList, shipRouteMap);
  // printShipRouteMap(shipRouteMap);

  // read cargo
  std::vector<Cargo *> cargoList;
  std::ifstream f2(argv[2]);
  if (!f2) {
    std::cerr << "Failed to open the file " << argv[2] << std::endl;
    exit(EXIT_FAILURE);
  }
  readCargo(f2, cargoList);
  sortCargo(cargoList);
  f2.close();

  // load cargo
  for (Cargo * ca : cargoList) {
    handleCargo2(ca, shipRouteMap[ca->getRoute()]);
  }

  // print in the order in input file
  printCargo(shipList);

  // delete ships and cargoes
  for (Ship * sh : shipList) {
    delete sh;
  }
  for (Cargo * ca : cargoList) {
    delete ca;
  }
  return 0;
}
