#pragma once  // make sure repeteted include of a hpp file is ingnored
#include <stdlib.h>

#include <cstdint>
#include <string>
#include <vector>

// friend specification is not declaration, need to be declared again
class Ship;
class Container;
class Tanker;
class AnimalShip;

class Cargo {
 protected:
  std::string name;
  std::string source;
  std::string destination;
  uint64_t weight;
  // type: container, liquid, gas, animal, roamer
  std::string shippingType;
  // harzardous properties
  std::vector<std::string> properties;
  // for fluids
  int minTemp;
  int maxTemp;

 public:
  Cargo() {}
  Cargo(std::string & s,
        std::string & src,
        std::string & dest,
        uint64_t x,
        std::string & type) :
      name(s), source(src), destination(dest), weight(x), shippingType(type) {}
  std::string getName() const { return name; }
  std::string getSrc() const { return source; }
  std::string getDest() const { return destination; }

  // if this cargo has any hazard property
  bool isHazard() { return !properties.empty(); }
  void setTempRange(int min, int max) {
    minTemp = min;
    maxTemp = max;
  }
  void addProperty(std::string const & s) { properties.push_back(s); }
  std::string getType() { return shippingType; }
  // friend is not inheritable
  friend class Ship;
  friend class Container;
  friend class Tanker;
  friend class AnimalShip;
};
/*
class Fluid : public Cargo {
 protected:
  int mintemp;
  int maxtemp;

  // friend is not inheritable
  friend class Ship;
  friend class Tanker;
};

class Animal {
 protected:
  std::string name;
  std::string source;
  std::string destination;
  uint64_t weight;
  bool isRoamer;

  friend class Ship;
  friend class AnimalShip;
};
*/
