#ifndef _BSTMAP_H__
#define _BSTMAP_H__
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "map.h"
// sorted according to key, not value!
template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  //Nodes
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    //constructor for Nodes
    Node() : key(0), value(0), left(NULL), right(NULL) {}
    //constructor for add
    Node(const K & k, const V & v) : key(k), value(v), left(NULL), right(NULL) {}
  };
  //root
 public:
  Node * root;

 public:
  //default constructor
  BstMap() : root(NULL) {}

  //copy constructor
  BstMap(const BstMap & rhs) : root(NULL) { root = copy(rhs.root); }

  //copy helper
  Node * copy(Node * current) {
    if (current == NULL) {
      return NULL;
    }
    Node * root = new Node(current->key, current->value);
    root->left = copy(current->left);
    root->right = copy(current->right);
    return root;
  }

  //assignment constructor
  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      destroy(root);
      root = copy(rhs.root);
    }
    return *this;
  }
  void inorder(Node * root) {
    if (!root)
      return;
    inorder(root->left);
    std::cout << root->key << ":" << root->value << std::endl;
    inorder(root->right);
  }

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
    if (*temp == NULL) {
      throw std::invalid_argument("Key not found!");
    }
    else {
      return (*temp)->value;
    }
  }

  // return the node to replace the deleted place
  Node * deleteNode(Node * root, const K & key) {
    if (!root) {
      return NULL;
    }
    if (key < root->key) {
      root->left = deleteNode(root->left, key);
    }
    else if (key > root->key) {
      root->right = deleteNode(root->right, key);
    }
    else {
      // 1.n0/n1: replace with NULL/only child
      if (!root->left) {
        Node * temp = root->right;
        delete root;
        root = NULL;
        return temp;
      }
      // 2.n1: replace with only child
      else if (!root->right) {
        Node * temp = root->left;
        delete root;
        root = NULL;
        return temp;
      }
      // 3.n2: replace with rightMin
      else {
        Node * temp = root->right;
        while (temp->left) {
          temp = temp->left;
        }
        root->key = temp->key;
        root->value = temp->value;
        root->right = deleteNode(root->right, temp->key);
      }
    }
    return root;
  }

  // if key not find, just don't delete
  virtual void remove(const K & key) { root = deleteNode(root, key); }
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
  virtual ~BstMap<K, V>() { destroy(root); }
  void destroy(Node * cur) {
    if (cur) {
      destroy(cur->left);
      destroy(cur->right);
      delete cur;
    }
  }
};

#endif
