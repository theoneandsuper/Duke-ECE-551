#ifndef __BSTSET_H__
#define __BSTSET_H__

#include "set.h"

template<typename T>
class BstSet : public Set<T> {
 private:
  struct Node {
    T key;
    Node * left;
    Node * right;
    Node(const T & k) : key(k), left(NULL), right(NULL) {}
  };

  Node * root;

  Node * copyTree(const Node * other) {
    if (other == NULL) {
      return NULL;
    }
    Node * n = new Node(other->key);
    n->left = copyTree(other->left);
    n->right = copyTree(other->right);
    return n;
  }

  void destroyTree(Node * cur) {
    if (cur != NULL) {
      destroyTree(cur->left);
      destroyTree(cur->right);
      delete cur;
    }
  }

  Node * addNode(Node * cur, const T & key) {
    if (cur == NULL) {
      return new Node(key);
    }
    if (key < cur->key) {
      cur->left = addNode(cur->left, key);
    }
    else if (cur->key < key) {
      cur->right = addNode(cur->right, key);
    }
    else {
      return cur;
    }
    return cur;
  }

  bool containsNode(const Node * cur, const T & key) const {
    if (cur == NULL) {
      return false;
    }
    if (key < cur->key) {
      return containsNode(cur->left, key);
    }
    else if (cur->key < key) {
      return containsNode(cur->right, key);
    }
    else {
      return true;
    }
  }

  Node * removeNode(Node * cur, const T & key) {
    if (cur == NULL) {
      return NULL;
    }
    if (key < cur->key) {
      cur->left = removeNode(cur->left, key);
      return cur;
    }
    else if (cur->key < key) {
      cur->right = removeNode(cur->right, key);
      return cur;
    }
    else {
      if (cur->left == NULL && cur->right == NULL) {
        delete cur;
        return NULL;
      }
      if (cur->left == NULL) {
        Node * temp = cur->right;
        delete cur;
        return temp;
      }
      if (cur->right == NULL) {
        Node * temp = cur->left;
        delete cur;
        return temp;
      }
      Node * succ = cur->right;
      while (succ->left != NULL) {
        succ = succ->left;
      }
      cur->key = succ->key;
      cur->right = removeNode(cur->right, succ->key);
      return cur;
    }
  }

 public:
  BstSet() : root(NULL) {}

  BstSet(const BstSet & rhs) : root(NULL) {
    root = copyTree(rhs.root);
  }

  BstSet & operator=(const BstSet & rhs) {
    if (this != &rhs) {
      Node * new_root = copyTree(rhs.root);
      destroyTree(root);
      root = new_root;
    }
    return *this;
  }

  virtual ~BstSet() {
    destroyTree(root);
  }

  virtual void add(const T & key) {
    root = addNode(root, key);
  }

  virtual bool contains(const T & key) const {
    return containsNode(root, key);
  }

  virtual void remove(const T & key) {
    root = removeNode(root, key);
  }
};

#endif

