#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>
#include <stdlib.h>

#include <cstdlib>
#include <exception>
#include <iostream>

//YOUR CODE GOES HERE
class Tester;

class OutOfRangeException : public std::exception {
 public:
  const char * what() const throw() { return "Index out of range!\n"; }
};

template<typename T>
class LinkedList {
 private:
  class Node {
   public:  // need to be public, or LinkedList won't be able to access them.
    T data;
    Node * next;
    Node * prev;

   public:
    Node(T x) : data(x), next(NULL), prev(NULL) {}
    Node(T x, Node * n, Node * p) : data(x), next(n), prev(p) {}
    Node(const Node & rhs) : data(rhs.data), next(rhs.next), prev(rhs.prev) {}
  };

  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    Node * temp = rhs.head;
    while (temp) {
      addBack(temp->data);
      temp = temp->next;
    }
  }
  LinkedList operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      removeList();
      Node * temp = rhs.head;
      while (temp) {
        addBack(temp->data);
        temp = temp->next;
      }
    }
    assert(size == rhs.size);
    return *this;
  }
  ~LinkedList() { removeList(); }

  void removeList() {
    Node * temp = head;
    while (temp) {
      Node * curr = temp->next;
      delete temp;
      temp = curr;
      --size;
    }
    assert(size == 0);
    head = NULL;
    tail = NULL;
  }

  void addFront(const T & item) {
    Node * temp = new Node(item, head, NULL);
    if (head) {
      head->prev = temp;
    }
    else {
      tail = temp;
    }
    head = temp;
    ++size;
  }
  void addBack(const T & item) {
    Node * temp = new Node(item, NULL, tail);
    if (tail) {
      tail->next = temp;
    }
    else {
      head = temp;
    }
    tail = temp;
    ++size;
  }
  /*return true if an item was actually removed and 
    false if no such item existed, only remove the 
    first item (starting from the head) if there are 
    multiple items that match*/
  bool remove(const T & item) {
    Node * temp = head;
    while (temp) {
      if (temp->data == item)
        break;
      temp = temp->next;
    }
    if (temp == NULL)
      return false;
    if (size == 1) {
      head = NULL;
      tail = NULL;
    }
    else if (temp == head) {
      head = temp->next;
      temp->next->prev = NULL;
    }
    else if (temp == tail) {
      tail = temp->prev;
      temp->prev->next = NULL;
    }
    else {
      temp->prev->next = temp->next;
      temp->next->prev = temp->prev;
    }
    delete (temp);
    --size;
    return true;
  }
  const T & operator[](int index) const {
    if (index < 0 || index >= size) {
      throw OutOfRangeException();
    }
    const Node * curr = head;
    for (int i = 0; i < index; ++i) {
      curr = curr->next;
    }
    return curr->data;
  }
  T & operator[](int index) {
    if (index < 0 || index >= size) {
      throw OutOfRangeException();
    }
    Node * curr = head;
    for (int i = 0; i < index; ++i) {
      curr = curr->next;
    }
    return curr->data;
  }
  int find(const T & item) const {
    const Node * temp = head;
    for (int i = 0; i < size; ++i) {
      if (temp->data == item) {
        return i;
      }
    }
    return -1;
  }
  int getSize() const { return size; }

  friend class Tester;
};

#endif
