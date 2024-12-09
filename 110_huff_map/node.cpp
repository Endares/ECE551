#include "node.h"
/* build map of all leaf Nodes under Node(*this) recursively */
void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  //WRITE ME!
  // leaf node
  if (sym != NO_SYM) {
    assert(!left && !right);
    theMap[sym] = b;
  }
  // not leaf node, must have 2 children
  else {
    assert(left);
    left->buildMap(b.plusZero(), theMap);
    assert(right);
    right->buildMap(b.plusOne(), theMap);
  }
}
