#ifndef __BSTMAP_H__
#define __BSTMAP_H__

#include <stdexcept>
#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  struct Node {
    K key;
    V value;
    Node * left;
    Node * right;
    Node(const K & k, const V & v) : key(k), value(v), left(NULL), right(NULL) {}
  };

  Node * root;

  Node * copyTree(const Node * other) {
    if (other == NULL) {
      return NULL;
    }
    Node * n = new Node(other->key, other->value);
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

  Node * addNode(Node * cur, const K & key, const V & value) {
    if (cur == NULL) {
      return new Node(key, value);
    }
    if (key < cur->key) {
      cur->left = addNode(cur->left, key, value);
    }
    else if (cur->key < key) {
      cur->right = addNode(cur->right, key, value);
    }
    else {
      cur->value = value;
    }
    return cur;
  }

  const V & lookupNode(const Node * cur, const K & key) const throw(std::invalid_argument) {
    if (cur == NULL) {
      throw std::invalid_argument("Key not found");
    }
    if (key < cur->key) {
      return lookupNode(cur->left, key);
    }
    else if (cur->key < key) {
      return lookupNode(cur->right, key);
    }
    else {
      return cur->value;
    }
  }

  Node * removeNode(Node * cur, const K & key) {
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
      Node * succ_parent = cur;
      Node * succ = cur->right;
      while (succ->left != NULL) {
        succ_parent = succ;
        succ = succ->left;
      }
      cur->key = succ->key;
      cur->value = succ->value;
      if (succ_parent->left == succ) {
        succ_parent->left = removeNode(succ_parent->left, succ->key);
      }
      else {
        succ_parent->right = removeNode(succ_parent->right, succ->key);
      }
      return cur;
    }
  }

 public:
  BstMap() : root(NULL) {}

  BstMap(const BstMap & rhs) : root(NULL) {
    root = copyTree(rhs.root);
  }

  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      Node * new_root = copyTree(rhs.root);
      destroyTree(root);
      root = new_root;
    }
    return *this;
  }

  virtual ~BstMap() {
    destroyTree(root);
  }

  virtual void add(const K & key, const V & value) {
    root = addNode(root, key, value);
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    return lookupNode(root, key);
  }

  virtual void remove(const K & key) {
    root = removeNode(root, key);
  }
};

#endif

