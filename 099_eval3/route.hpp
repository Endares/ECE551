#include <stdlib.h>

#include <cstdint>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class Routes {
 private:
  int sz;  // number of islands
  std::unordered_map<std::string, int> islandSet;
  std::vector<std::vector<std::pair<int, uint64_t> > > adjacentList;

 public:
  Routes(){};
  Routes(int sz) : sz(sz) { adjacentList.resize(sz); }

  void addRoute(std::string src, std::string dest, uint64_t cap) {
    if (islandSet.find(src) == islandSet.end()) {
      islandSet.insert({src, sz});
      ++sz;
      // 2-d vector resize: if expand, will not change each row's columns automatically.
      adjacentList.resize(sz);
    }
    if (islandSet.find(dest) == islandSet.end()) {
      islandSet.insert({dest, sz});
      ++sz;
      // 2-d vector resize: if expand, will not change each row's columns automatically.
      adjacentList.resize(sz);
    }
    int s = islandSet[src];
    int d = islandSet[dest];
    for (int i = 0; i < (int)adjacentList[s].size(); ++i) {
    }
  }
};
