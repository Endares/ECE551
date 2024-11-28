#pragma once
#include <stdlib.h>

#include <cassert>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

#include "cargo1.hpp"
class Ship {
 protected:          // need to be accessed by son
  std::string name;  // must be unique
  std::string source;
  std::string destination;
  uint64_t capacity;
  uint64_t load;  // currently-used capacity
  std::vector<Cargo *> cargoes;

 public:
  Ship() : capacity(0), load(0) {}
  // load is 0 when initialized
  Ship(const std::string & s,
       const std::string & src,
       const std::string & dest,
       uint64_t cap) :
      name(s), source(src), destination(dest), capacity(cap), load(0) {}
  virtual ~Ship() {}
  std::string getName() const { return name; }
  // shouldn't be abstract, as AnimalShip doesn't have this method.
  virtual void addProperty(std::string & p){};

  virtual void addCargo(Cargo * c) {
    cargoes.push_back(c);
    load += c->weight;
  }

  virtual bool canAdd(Cargo * c) const = 0;
  virtual void printStatus() const = 0;
  // calculate remaining capacity
  uint64_t getRemain() const {
    assert(load <= capacity);
    return capacity - load;
  }
};

class Container : public Ship {
 protected:
  size_t slotNum;
  std::unordered_set<std::string> properties;

 public:
  Container() : Ship(), slotNum(0) {}
  Container(const std::string & name,
            const std::string & source,
            const std::string & destination,
            uint64_t capacity,
            size_t slots) :
      Ship(name, source, destination, capacity), slotNum(slots) {}

  virtual void addProperty(std::string & p) override { properties.insert(p); }

  // if a cargo can be added to a container
  virtual bool canAdd(Cargo * c) const override;
  virtual void printStatus() const override;
};

class Tanker : public Ship {
 protected:
  size_t tankNum;
  uint64_t tankVolumn;
  // <substance name, load> of each tank
  std::vector<std::pair<std::string, uint64_t> > tanks;
  int minTemp, maxTemp;
  std::unordered_set<std::string> properties;

 public:
  Tanker() : Ship(), tankNum(0) {}
  Tanker(const std::string & name,
         const std::string & source,
         const std::string & destination,
         uint64_t capacity,
         size_t tankNumber,
         int min,
         int max) :
      Ship(name, source, destination, capacity),
      tankNum(tankNumber),
      minTemp(min),
      maxTemp(max) {
    // volumn of each tank
    tankVolumn = capacity / tankNum;
    // initialize each tank as empty
    tanks.resize(tankNum);
    for (auto & p : tanks) {
      p.first = "";
      p.second = 0;
    }
  }

  virtual void addProperty(std::string & p) override { properties.insert(p); }
  virtual bool canAdd(Cargo * c) const override;
  void addToTank(Cargo * c);
  virtual void addCargo(Cargo * c) override;
  virtual void printStatus() const override;
};
class AnimalShip : public Ship {
 protected:
  // max capacity of cargoes.
  uint64_t threshold;

 public:
  bool hasRoamer;

 public:
  AnimalShip() : Ship() {}
  AnimalShip(const std::string & name,
             const std::string & source,
             const std::string & destination,
             uint64_t capacity,
             uint64_t thres) :
      Ship(name, source, destination, capacity), threshold(thres), hasRoamer(false) {}
  // ship with a roamer can't have any other animals
  virtual bool canAdd(Cargo * c) const override;
  virtual void addCargo(Cargo * c) override;
  virtual void printStatus() const override;
};

/* Container */

// if a cargo can be added to a container
bool Container::canAdd(Cargo * c) const {
  // if the cargo has the "container" type
  if (c->shippingType != "container") {
    return false;
  }
  // container is full
  if (cargoes.size() >= slotNum) {
    return false;
  }
  // different route
  if (c->destination != destination || c->source != source) {
    return false;
  }
  // the container has sufficient capacity remaining
  // can't use subtraction here. unsigned!
  if (c->weight + load > capacity) {
    return false;
  }
  // hazmat test
  for (const std::string & s : c->properties) {
    if (properties.find(s) == properties.end()) {
      return false;
    }
  }
  return true;
}

void Container::printStatus() const {
  std::cout << "The Container Ship " << name << "(" << load << "/" << capacity
            << ") is carrying : " << std::endl;
  for (Cargo * c : cargoes) {
    std::cout << "  " << c->name << "(" << c->weight << ")" << std::endl;
  }
  std::cout << "  (" << slotNum - cargoes.size() << ") slots remain" << std::endl;
}

/* Tanker */
void Tanker::addCargo(Cargo * c) {
  cargoes.push_back(c);
  load += c->weight;
  addToTank(c);
}
void Tanker::addToTank(Cargo * c) {
  uint64_t w = c->weight;
  size_t i = 0;
  while (i < tankNum && w != 0) {
    // make sure uint substraction won't < 0
    assert(tanks[i].second <= tankVolumn);
    // add to an empty tank
    if (tanks[i].first == "") {
      tanks[i].first = c->name;
      tanks[i].second = std::min(tankVolumn, w);
      assert(w >= tanks[i].second);
      w -= tanks[i].second;
    }
    // add to a non-empty tank
    else if (tanks[i].first == c->name) {
      uint64_t temp = std::min(tankVolumn - tanks[i].second, w);
      assert(w >= temp);
      w -= temp;
      tanks[i].second += temp;
    }
    // make sure uint substraction won't < 0
    assert(tanks[i].second <= tankVolumn);
    ++i;
  }
}

bool Tanker::canAdd(Cargo * c) const {
  // if the cargo has the "liquid" or "gas" type
  if (c->shippingType != "liquid" && c->shippingType != "gas") {
    return false;
  }
  // different route
  if (c->destination != destination || c->source != source) {
    return false;
  }
  // hazmat test
  for (const std::string & s : c->properties) {
    if (properties.find(s) == properties.end()) {
      return false;
    }
  }
  // temperature range of the ship and the cargo has intersection
  if (c->maxTemp < minTemp || c->minTemp > maxTemp) {
    return false;
  }
  // the tanker has sufficient capacity remaining
  // can't use subtraction here. unsigned!
  uint64_t remainCap = 0;
  for (size_t i = 0; i < tankNum; ++i) {
    // make sure uint substraction won't < 0
    assert(tanks[i].second <= tankVolumn);
    if (tanks[i].first == "") {
      remainCap += tankVolumn;
    }
    else if (tanks[i].first == c->name) {
      remainCap += tankVolumn - tanks[i].second;
    }
  }
  return remainCap >= c->weight;
}

void Tanker::printStatus() const {
  size_t tankUsed = 0;
  for (auto & p : tanks) {
    if (p.first != "") {
      ++tankUsed;
    }
  }
  std::cout << "The Tanker Ship " << name << "(" << load << "/" << capacity
            << ") is carrying : " << std::endl;
  for (Cargo * c : cargoes) {
    std::cout << "  " << c->name << "(" << c->weight << ")" << std::endl;
  }
  std::cout << "  " << tankUsed << " / " << tankNum << " tanks used" << std::endl;
}

/* AnimalShip */
bool AnimalShip::canAdd(Cargo * c) const {
  // same route
  if (c->destination != destination || c->source != source) {
    return false;
  }
  // can fit on the ship
  if (c->weight + load > capacity) {
    return false;
  }

  // 1. container cargo
  if (c->shippingType == "container") {
    // not hazardous
    if (c->isHazard()) {
      return false;
    }
    // small enough, smaller than threshold
    if (c->weight > threshold) {
      return false;
    }
    return true;
  }
  // 2. if the cargo has the "animal" type, which is not a roamer
  else if (c->shippingType == "animal") {
    return true;
  }
  // 3. if the cargo has the "roamer" type, each animal ship allow at most one roamer
  else if (c->shippingType == "roamer") {
    return !hasRoamer;
  }
  return false;
}
void AnimalShip::addCargo(Cargo * c) {
  cargoes.push_back(c);
  load += c->weight;
  if (c->shippingType == "roamer") {
    hasRoamer = true;
  }
}

void AnimalShip::printStatus() const {
  std::cout << "The Animals Ship " << name << "(" << load << "/" << capacity
            << ") is carrying : " << std::endl;
  for (Cargo * c : cargoes) {
    std::cout << "  " << c->name << "(" << c->weight << ")" << std::endl;
  }
  std::cout << (hasRoamer ? "  has a roamer" : "  does not have a roamer") << std::endl;
}
