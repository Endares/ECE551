#pragma once
#include <stdlib.h>

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

#include "cargo.hpp"
class Ship {
 protected:          // need to be accessed by son
  std::string name;  // must be unique
  std::string source;
  std::string destination;
  uint64_t capacity;
  uint64_t load;  // currently-used capacity

 public:
  Ship() : capacity(0), load(0) {}
  // load is 0 when initialized
  Ship(const std::string & s,
       const std::string & src,
       const std::string & dest,
       uint64_t cap) :
      name(s), source(src), destination(dest), capacity(cap), load(0) {}

  Ship(const Ship & rhs) :
      name(rhs.name),
      source(rhs.source),
      destination(rhs.destination),
      capacity(rhs.capacity),
      load(rhs.load) {}
  std::string getName() const { return name; }
};

class Container : public Ship {
 private:
  size_t slotNum;
  std::unordered_set<std::string> properties;
  std::vector<Cargo> cargoes;

 public:
  Container() : Ship(), slotNum(0) {}
  Container(const std::string & name,
            const std::string & source,
            const std::string & destination,
            uint64_t capacity,
            size_t slots) :
      Ship(name, source, destination, capacity), slotNum(slots) {}
  Container(const Container & rhs) :
      Ship(rhs), slotNum(rhs.slotNum), properties(rhs.properties), cargoes(rhs.cargoes) {}

  void addProperty(std::string p) { properties.insert(p); }

  void addCargo(Cargo & c) {
    cargoes.push_back(c);
    load += c.weight;
  }
  // if a cargo can be added to a container
  bool canAdd(Cargo & c) const {
    // if the cargo has the "container" property
    if (c.shippingType != "container") {
      return false;
    }
    // container is full
    if (cargoes.size() >= slotNum) {
      return false;
    }
    // different route
    if (c.destination != destination || c.source != source) {
      return false;
    }
    // the cargo ship has sufficient capacity remaining
    // can't use subtraction here. unsigned!
    if (c.weight + load > capacity) {
      return false;
    }
    // hazmat test
    for (const std::string & s : c.properties) {
      if (properties.find(s) == properties.end()) {
        return false;
      }
    }
    return true;
  }

  // make a container from read data
  // member method to visit protected fields
  void setContainer(std::string & cname,
                    std::string & src,
                    std::string & dest,
                    uint64_t cap,
                    size_t slots,
                    std::unordered_set<std::string> hazmat) {
    name = cname;
    source = src;
    destination = dest;
    capacity = cap;
    slotNum = slots;
    load = 0;
    properties = hazmat;
  }

  void printStatus() {
    std::cout << "The Container Ship " << name << "(" << load << "/" << capacity
              << ") is carrying : " << std::endl;
    for (Cargo c : cargoes) {
      std::cout << "  " << c.name << "(" << c.weight << ")" << std::endl;
    }
    std::cout << "  (" << slotNum - cargoes.size() << ") slots remain" << std::endl;
  }
};
