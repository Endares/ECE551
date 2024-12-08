#ifndef _BSTMAP_H__
#define _BSTMAP_H__

#include <cstdlib>

#include "map.h"
// sorted according to key, not value!
template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;

   public:
    Node() {}
    Node(const K & key, const V & value) :
        key(key), value(value), left(NULL), right(NULL) {}
  };
  Node * root;

 public:
  BstMap() : root(NULL) {}  // don't forget to initialize

  //copy constructor
  //BstMap(const BstMap & rhs) : root(NULL) { root = copy(rhs.root); }

  //copy helper
  /*Node * copy(Node * current) {
    if (current == NULL) {
      return NULL;
    }
    Node * root = new Node(current->key, current->value);
    root->left = copy(current->left);
    root->right = copy(current->right);
    return root;
  }
  */
  //assignment constructor
  /*BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      destroy(root);
      root = copy(rhs.root);
    }
    return *this;
    }*/

  virtual void add(const K & key, const V & value) {
    Node ** temp = find(key);
    // doubly ptr to make sure new Node is inserted into the BST.

    if (*temp) {
      (*temp)->value = value;
    }
    else {
      temp = &root;
      while (*temp) {
        if (key > (*temp)->key) {
          temp = &(*temp)->right;
        }
        else {
          temp = &(*temp)->left;
        }
      }
      *temp = new Node(key, value);
    }
  }
  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node ** temp = find(key);
    if (!(*temp)) {
      throw std::invalid_argument("Key not found!");
    }
    else {
      return (*temp)->value;
    }
  }
  virtual void remove(const K & key) {
    Node ** temp = find(key);
    if (!(*temp)) {
      throw std::invalid_argument("Key not found!");
    }
    else {
      if (!(*temp)->left && !(*temp)->right) {
        delete (*temp);
        // set *temp to NULL, in case of duplicated delete when destruction
        *temp = NULL;
      }
      else if (!(*temp)->left) {
        Node ** substitute = findRightMin(*temp);
        (*temp)->key = (*substitute)->key;
        (*temp)->value = (*substitute)->value;
        delete *substitute;
        *substitute = NULL;
      }
      else {
        Node ** substitute = findLeftMax(*temp);
        (*temp)->key = (*substitute)->key;
        (*temp)->value = (*substitute)->value;
        delete *substitute;
        *substitute = NULL;
      }
    }
  }

  Node ** findRightMin(Node * cur) const {
    Node ** temp = &cur;
    temp = &(*temp)->right;
    while (*temp && (*temp)->left) {
      temp = &(*temp)->left;
    }
    return temp;
  }

  Node ** findLeftMax(Node * cur) const {
    Node ** temp = &cur;
    temp = &(*temp)->left;
    while (*temp && (*temp)->right) {
      temp = &(*temp)->right;
    }
    return temp;
  }

  Node ** find(const K & key) const {
    Node ** temp = const_cast<Node **>(&root);
    while (*temp) {
      if (key > (*temp)->key) {
        temp = &(*temp)->right;
      }
      else if (key < (*temp)->key) {
        temp = &(*temp)->left;
      }
      else {
        return temp;
      }
    }
    return temp;
  }
  virtual ~BstMap<K, V>() {
    // destroy(root);
    // root = NULL;
  }
  void destroy(Node * cur) {
    if (cur) {
      destroy(cur->left);
      destroy(cur->right);
      delete cur;
    }
  }
};

#endif
