#include <stdlib.h>

#include <cstdint>
#include <string>
#include <vector>
class Ship {
 private:
  std::string name;
  std::string source;
  std::string destination;
  uint64_t capacity;

 public:
  Ship() : capacity(0) {}
  Ship(std::string s, std::string src, std::string dest, uint64_t cap) :
      name(s), source(s), destination(dest), capacity(cap) {}
};
