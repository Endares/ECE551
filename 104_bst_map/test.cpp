#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "bstmap.h"

int main(void) {
  BstMap<int, int> map;
  std::cout << "0" << std::endl;
  map.add(60, 1);
  std::cout << "1" << std::endl;
  map.add(19, 2);
  map.add(93, 3);
  map.add(4, 4);
  map.add(25, 5);
  map.add(84, 6);
  map.add(1, 7);
  map.add(11, 8);
  map.add(21, 9);
  map.add(35, 10);
  map.add(70, 11);
  map.add(86, 12);
  map.inorder(map.root);
  std::cout << "\n";
  int ans1 = map.lookup(60);
  int ans2 = map.lookup(35);
  map.remove(19);
  std::cout << "\n";
  std::cout << "ans1 should be 1 and =" << ans1 << "\n";
  std::cout << "ans2 should be 10 and =" << ans2 << "\n";
  map.inorder(map.root);
  return EXIT_SUCCESS;
}
