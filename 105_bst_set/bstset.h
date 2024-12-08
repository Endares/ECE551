#ifndef __BSTSET_H__
#define __BSTSET_H__
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "set.h"
// sorted according to key, not value!
template<typename K>
class BstSet : public Set<K> {
 private:
  //Nodes
  class Node {
   public:
    K key;
    Node * left;
    Node * right;
    //constructor for Nodes
    Node() : key(0), left(NULL), right(NULL) {}
    //constructor for add
    Node(const K & k) : key(k), left(NULL), right(NULL) {}
  };
  //root
 public:
  Node * root;

 public:
  //default constructor
  BstSet() : root(NULL) {}

  //copy constructor
  BstSet(const BstSet & rhs) : root(NULL) { root = copy(rhs.root); }

  //copy helper
  Node * copy(Node * current) {
    if (current == NULL) {
      return NULL;
    }
    Node * root = new Node(current->key);
    root->left = copy(current->left);
    root->right = copy(current->right);
    return root;
  }

  //assignment constructor
  BstSet & operator=(const BstSet & rhs) {
    if (this != &rhs) {
      // Method 1: copy
      // destroy(root);
      // root = copy(rhs.root);
      // Method 2: swap and auto delete when temp is out of scope
      BstSet<K> temp(rhs);
      std::swap(root, temp.root);
    }
    return *this;
  }
  void inorder(Node * root) {
    if (!root)
      return;
    inorder(root->left);
    std::cout << root->key << std::endl;
    inorder(root->right);
  }

  virtual void add(const K & key) {
    Node ** temp = find(key);
    // doubly ptr to make sure new Node is inserted into the BST.

    if (*temp) {
      ;
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
      *temp = new Node(key);
    }
  }

  virtual bool contains(const K & key) const {
    Node ** temp = find(key);
    return (*temp) != NULL;
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
  virtual ~BstSet<K>() { destroy(root); }
  void destroy(Node * cur) {
    if (cur) {
      destroy(cur->left);
      destroy(cur->right);
      delete cur;
    }
  }
};

#endif
