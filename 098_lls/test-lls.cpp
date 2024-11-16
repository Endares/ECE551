#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "ll.hpp"
typedef LinkedList<int> IntList;

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME
    IntList il;
    il.addFront(10);
    assert(il.head != NULL);
    assert(il.head->data == 10);
    assert(il.getSize() == 1);

    IntList::Node * curr = il.head;
    il.addFront(20);
    assert(il.head->data == 20);
    assert(curr->prev->data == 20);
    assert(curr == il.tail);
    assert(il.head->prev == NULL && il.tail->next == NULL);
  }

  void testAddBack() {
    IntList il;
    il.addBack(1);
    il.addBack(2);
    assert(il.head->data == 1 && il.head->next->data == 2);
    assert(il.getSize() == 2);
    assert(il.tail->data == 2 && il.tail->prev->data == 1);
  }

  // many more tester methods
  void testCpyCtor() {
    IntList il1;
    il1.addFront(1);
    il1.addBack(2);
    il1.addFront(3);

    IntList il2(il1);
    assert(il2.getSize() == il1.getSize());  // Sizes should be equal
    IntList::Node * node1 = il1.head;
    IntList::Node * node2 = il2.head;

    while (node1 != NULL && node2 != NULL) {
      assert(node1->data == node2->data);  // Values should match
      node1 = node1->next;
      node2 = node2->next;
    }
    assert(node1 == NULL && node2 == NULL);  // Both lists should end at the same time

    node1 = il1.tail;
    node2 = il2.tail;

    while (node1 != NULL && node2 != NULL) {
      assert(node1->data == node2->data);
      node1 = node1->prev;
      node2 = node2->prev;
    }
    assert(node1 == NULL && node2 == NULL);
  }

  void testRemoval() {
    IntList a;
    assert(a.remove(1) == false);
    a.addBack(1);
    a.addBack(2);
    a.addBack(3);
    a.addBack(4);
    a.addBack(5);
    //a : 1 2 3 4 5
    a.remove(1);
    //a : 2 3 4 5
    assert(a.getSize() == 4 && a.head->data == 2 && a.head->next->data == 3 &&
           a.head->prev == NULL);
    assert(a.remove(1) == false);
    a.remove(5);
    //a : 2 3 4
    assert(a.getSize() == 3 && a.head->data == 2 && a.tail->data == 4 &&
           a.tail->next == NULL && a.head->next == a.tail->prev);
    a.remove(3);
    // Expected: a = 2 4
    assert(a.getSize() == 2);
    assert(a.head->data == 2 && a.head->next->data == 4);
    assert(a.tail->data == 4 && a.tail->prev->data == 2);
    a.remove(2);
    a.remove(4);
    assert(a.getSize() == 0 && a.head == NULL && a.tail == NULL);
  }
  void testRuleofThree() {
    IntList list1;
    list1.addFront(1);
    list1.addBack(2);  //[1,2]
    IntList list2(list1);
    assert(list2.getSize() == 2 && list2.head->data == 1 && list2.head->next->data == 2 &&
           list2.head->next == list2.tail && list2.tail->prev == list2.head &&
           list2.head->prev == NULL && list2.head->prev == list2.tail->next);
    list1.remove(2);  //[1]
    list2 = list1;    //[1]
    assert(list2.getSize() == 1 && list2.head->data == 1 && list2.head == list2.tail &&
           list2.head->next == NULL && list2.head->next == list2.head->prev);
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  // write calls to your other test methods here
  t.testAddBack();
  t.testCpyCtor();
  t.testRemoval();
  t.testRuleofThree();
  return EXIT_SUCCESS;
}
