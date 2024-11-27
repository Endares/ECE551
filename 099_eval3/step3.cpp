#include "step3.hpp"

#include <stdlib.h>

#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

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
  // Ship* in input  order
  std::vector<Ship *> shipList;
  readShipFile(f, shipList);
  f.close();

  // read cargo
  std::vector<Cargo *> cargoList;
  std::ifstream f2(argv[2]);
  if (!f2) {
    std::cerr << "Failed to open the file " << argv[2] << std::endl;
    exit(EXIT_FAILURE);
  }
  readCargo(f2, cargoList);
  f2.close();

  // load cargo
  for (Cargo * ca : cargoList) {
    handleCargo(ca, shipList);
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
