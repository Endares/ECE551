#include "node.h"
#include "readFreq.h"

priority_queue_t makePQ(uint64_t * counts) {
  priority_queue_t pq;
  for (size_t i = 0; i < NUMCHARS; ++i) {
    if (counts[i] != 0) {
      pq.push(new Node(i, counts[i]));
    }
  }
  return pq;
}

Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t pq = makePQ(counts);
  while (pq.size() > 1) {
    // smallest: right child; second smallest: left child
    Node * r = pq.top();
    pq.pop();
    Node * l = pq.top();
    pq.pop();
    pq.push(new Node(l, r));
  }
  return pq.top();
}
