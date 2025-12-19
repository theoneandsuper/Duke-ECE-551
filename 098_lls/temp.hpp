#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>

//YOUR CODE GOES HERE

template <typename T>
class LinkedList {
 private:
  // ====== Node (private inner class) ======
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;

    Node(const T & d, Node * p = NULL, Node * n = NULL) :
        data(d), next(n), prev(p) {}
  };

  Node * head;
  Node * tail;
  int size;

  // helper: delete all nodes
  void clear() {
    Node * curr = head;
    while (curr != NULL) {
      Node * nxt = curr->next;
      delete curr;
      curr = nxt;
    }
    head = NULL;
    tail = NULL;
    size = 0;
  }

  // helper: copy all elements from other (used by copy ctor)
  void copyFrom(const LinkedList & rhs) {
    Node * curr = rhs.head;
    while (curr != NULL) {
      addBack(curr->data);
      curr = curr->next;
    }
  }

  // helper: get node pointer at index, or NULL if bad
  Node * getNodeAt(int index) const {
    if (index < 0 || index >= size) {
      return NULL;
    }
    Node * curr = head;
    for (int i = 0; i < index; i++) {
      curr = curr->next;
    }
    return curr;
  }

class BadIndex : public std::exception {
 public:
   virtual const char * what() const throw() {
    return "LinkedList index out of range";
  }
};

  // 
  LinkedList() : head(NULL), tail(NULL), size(0) {}

  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    copyFrom(rhs);
  }

  ~LinkedList() {
    clear();
  }

  // copy-and-swap assignment
  LinkedList & operator=(LinkedList rhs) {
    swap(rhs);
    return *this;
  }

  void swap(LinkedList & other) {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(size, other.size);
  }

  int getSize() const {
    return size;
  }

  // modifiers 

  // add item to front
  void addFront(const T & item) {
    Node * n = new Node(item, NULL, head);
    if (head != NULL) {
      head->prev = n;
    }
    head = n;
    if (tail == NULL) {
      tail = n;  // list was empty
    }
    size++;
  }

  // add item to back
  void addBack(const T & item) {
    Node * n = new Node(item, tail, NULL);
    if (tail != NULL) {
      tail->next = n;
    }
    tail = n;
    if (head == NULL) {
      head = n;  // list was empty
    }
    size++;
  }

  // remove first node whose data == item
  // return true if something was removed, false otherwise
  bool remove(const T & item) {
    Node * curr = head;
    while (curr != NULL && !(curr->data == item)) {
      curr = curr->next;
    }
    if (curr == NULL) {
      return false;  // not found
    }

    // relink neighbors
    if (curr->prev != NULL) {
      curr->prev->next = curr->next;
    }
    else {
      head = curr->next;  // removing head
    }
    if (curr->next != NULL) {
      curr->next->prev = curr->prev;
    }
    else {
      tail = curr->prev;  // removing tail
    }

    delete curr;
    size--;
    return true;
  }


  // non-const version
  T & operator[](int index) {
    Node * n = getNodeAt(index);
    if (n == NULL) {
      throw BadIndex();
    }
    return n->data;
  }

  // const version
  const T & operator[](int index) const {
    Node * n = getNodeAt(index);
    if (n == NULL) {
      throw BadIndex();
    }
    return n->data;
  }

  //search

  // return index of first item == item, or -1 if not found
  int find(const T & item) const {
    Node * curr = head;
    int idx = 0;
    while (curr != NULL) {
      if (curr->data == item) {
        return idx;
      }
      curr = curr->next;
      idx++;
    }
    return -1;
  }
};

#endif
