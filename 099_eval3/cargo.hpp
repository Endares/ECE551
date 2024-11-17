//#ifndef CARGO_HPP   // make sure Cargo is defined only once

//#define CARGO_HPP
#pragma once  // make sure repeteted include of a hpp file is ingnored
#include <stdlib.h>

#include <cstdint>
#include <string>
#include <vector>

// friend specification is not declaration, need to be declared again
class Ship;
class Container;

class Cargo {
 private:
  std::string name;
  std::string source;
  std::string destination;
  uint64_t weight;
  std::string shippingType;
  std::vector<std::string> properties;

 public:
  Cargo() {}
  Cargo(std::string & s,
        std::string & src,
        std::string & dest,
        uint64_t x,
        std::string & type,
        std::vector<std::string> & prop) :
      name(s),
      source(src),
      destination(dest),
      weight(x),
      shippingType(type),
      properties(prop) {}
  std::string getName() const { return name; }
  std::string getSrc() const { return source; }
  std::string getDest() const { return destination; }

  // friend is not inheritable
  friend class Ship;
  friend class Container;
};
