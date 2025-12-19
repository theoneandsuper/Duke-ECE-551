#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }

  bool checkList(const IntList & lst, const int * arr, int n) {
    // size
    assert(lst.getSize() == n);

    // from head 
    IntList::Node * cur = lst.head;
    IntList::Node * prev = NULL;
    int i = 0;
    while (cur != NULL) {
      assert(i < n);
      assert(cur->data == arr[i]);
      assert(cur->prev == prev);
      prev = cur;
      cur = cur->next;
      i++;
    }
    assert(i == n);
    assert(prev == lst.tail);

    // from tail
    cur = lst.tail;
    IntList::Node * next = NULL;
    i = n - 1;
    while (cur != NULL) {
      assert(i >= 0);
      assert(cur->data == arr[i]);
      assert(cur->next == next);
      next = cur;
      cur = cur->prev;
      i--;
    }
    assert(i == -1);
    assert(next == lst.head);
    return true;
  }

  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME
    IntList lst;
    lst.addFront(3);
    int a1[] = {3};
    checkList(lst, a1, 1);
    assert(lst.head == lst.tail);
    assert(lst.head->next == NULL);
    assert(lst.head->prev == NULL);

    lst.addFront(4); // 4,3
    int a2[] = {4, 3};
    checkList(lst, a2, 2);

    lst.addFront(1); // 1,4,3
    int a3[] = {1, 4, 3};
    checkList(lst, a3, 3);
    assert(lst[0] == 1);
  }
  // many more tester methods
  void testAddBack() {
    IntList lst;
    lst.addBack(5); // 5
    int a1[] = {5};
    checkList(lst, a1, 1);

    lst.addBack(7); // 5,7
    int a2[] = {5, 7};
    checkList(lst, a2, 2);
    assert(lst.tail == lst.head->next);
    assert(lst.head->next->prev == lst.head);
  }

  void testMixedAddAndLinks() {
    IntList lst;
    lst.addFront(4);  // 4
    lst.addBack(3);   // 4,3
    lst.addFront(1);  // 1,4,3
    lst.addBack(5);   // 1,4,3,5
    lst.addBack(7);   // 1,4,3,5,7
    int a[] = {1,4,3,5,7};
    checkList(lst, a, 5);
    assert(lst[1] == 4 && lst[2] == 3 && lst[4] == 7);
    assert(lst.head->prev == NULL);
    assert(lst.tail->next == NULL);
    assert(lst.head->next->prev == lst.head);
  }

  void testIndexAndFind() {
    IntList lst;
    lst.addBack(1);
    lst.addBack(3);
    lst.addBack(5);
    lst.addBack(7);  // 1,3,5,7
    int a[] = {1,3,5,7};
    checkList(lst, a, 4);
    assert(lst[0] == 1 && lst[1] == 3 && lst[2] == 5 && lst[3] == 7);
    assert(lst.find(5) == 2);
    assert(lst.find(1) == 0);
  }

  void testRemoveVariants() {
    // rm empty
    {
      IntList lst;
      assert(lst.remove(1) == false);
      assert(lst.getSize() == 0);
      assert(lst.head == NULL && lst.tail == NULL);
    }

    // rm only
    {
      IntList lst;
      lst.addBack(10);
      int a[] = {10};
      checkList(lst, a, 1);
      assert(lst.remove(10) == true);
      assert(lst.getSize() == 0);
      assert(lst.head == NULL && lst.tail == NULL);
    }

    // multiple 1,4,3,5,7 -> rm 4 -> rm 5 -> rm null
    {
      IntList lst;
      lst.addBack(1);
      lst.addBack(4);
      lst.addBack(3);
      lst.addBack(5);
      lst.addBack(7); // 1,4,3,5,7
      assert(lst.remove(4) == true); // 1,3,5,7
      int b[] = {1,3,5,7};
      checkList(lst, b, 4);
      assert(lst.find(5) == 2);

      assert(lst.remove(5) == true); // 1,3,7
      int c[] = {1,3,7};
      checkList(lst, c, 3);
      assert(lst.head->next == lst.tail->prev);

      assert(lst.remove(42) == false);
      checkList(lst, c, 3);
    }
  }

  void testAssignOp() {
    IntList src;
    src.addBack(1);
    src.addBack(3);
    src.addBack(7); // 1,3,7
    int a[] = {1,3,7};
    checkList(src, a, 3);

    IntList dst;
    dst = src;
    checkList(dst, a, 3);

    // dst affects src?
    assert(dst.remove(3) == true);
    int b[] = {1,7};
    checkList(dst, b, 2);
    checkList(src, a, 3); // src still 1,3,7

    assert(dst.head->next == dst.tail);
    assert(dst.tail->prev == dst.head);
    assert(dst.tail->next == NULL);
    assert(dst.head->prev == NULL);

    // rm null
    assert(dst.remove(3) == false);
  }

  void testCopyCtor() {
    IntList orig;
    orig.addBack(1);
    orig.addBack(3);
    orig.addBack(7);
    int a[] = {1,3,7};
    checkList(orig, a, 3);

    IntList cp(orig);
    checkList(cp, a, 3);

    // change cp but orig
    cp.remove(3);
    int b[] = {1,7};
    checkList(cp, b, 2);
    checkList(orig, a, 3);

    // assert
    assert(cp.head->next == cp.tail);
    assert(cp.tail->prev == cp.head);
    assert(cp.head->prev == NULL);
    assert(cp.tail->next == NULL);
  }

   void testSelfAssignNonEmpty() {
      IntList a;
      a.addBack(1); a.addBack(2); a.addBack(3);        // [1,2,3]
      a = a;
      int exp[] = {1,2,3};
      checkList(a, exp, 3);
      // add more to check
      a.addFront(0);
      a.addBack(4);                     // [0,1,2,3,4]
      int exp2[] = {0,1,2,3,4};
      checkList(a, exp2, 5);
  }
  
   void testAssignEmptyToNonEmpty() {
    IntList src;                                     // empty
    IntList dst;
    dst.addBack(10); 
    dst.addBack(20);                // both not empty
    dst = src;                                       // should be empty
    assert(dst.getSize() == 0);
    assert(dst.head == NULL && dst.tail == NULL);
  }

   void testAssignNonEmptyToEmpty() {
    IntList src; src.addBack(7); src.addBack(8);     // [7,8]
    IntList dst;                                     // empty
    dst = src;
    int exp[] = {7,8};
    checkList(dst, exp, 2);
    // deep copy test
    dst.remove(7);
    int expDst[] = {8};
    int expSrc[] = {7,8};
    checkList(dst, expDst, 1);
    checkList(src, expSrc, 2);
   }

  void testCopyCtorEmptyAndScope() {
    IntList empty;                                   // empty
    IntList cpy(empty);                              // empty copy
    assert(cpy.getSize() == 0 && cpy.head == NULL && cpy.tail == NULL);

    IntList orig; orig.addBack(1); orig.addBack(2);  // [1,2]
    {                                                
      IntList tmp(orig);
      int e[] = {1,2};
      checkList(tmp, e, 2);
    }                                                // orig should be fine
    int e2[] = {1,2};
    checkList(orig, e2, 2);
  }

  void testChainedAssign() {
    IntList a; a.addBack(1); a.addBack(2);           // [1,2]
    IntList b; b.addBack(3);                         // [3]
    IntList c; c.addBack(4); c.addBack(5); c.addBack(6); // [4,5,6]
    a = b = c;                                       // first b=c，then a=b
    int exp[] = {4,5,6};
    checkList(a, exp, 3);
    checkList(b, exp, 3);
    checkList(c, exp, 3);
  }

  void testRemoveFirstOccurrenceOnly() {
   {	  
    IntList lst;
    lst.addBack(2); 
    lst.addBack(2); 
    lst.addBack(2); 
    lst.addBack(3); // 2,2,2,3
    assert(lst.remove(2) == true);  // only the first
    int e[] = {2,2,3};
    checkList(lst, e, 3);
    assert(lst.head->data == 2);          // should still have 2 at front
    assert(lst.find(2) == 0);             // 
  }

  {
    IntList lst;
    lst.addBack(1); 
    lst.addBack(2); 
    lst.addBack(3); 
    lst.addBack(3); 
    lst.addBack(3); // 1,2,3,3,3
    assert(lst.remove(3) == true);   // rm only first 3（index=2）
    int e[] = {1,2,3,3};
    checkList(lst, e, 4);
   }
  }

  void testRemoveLen2Edges() {
  // [1,2] -> [1]
   {
    IntList lst;
    lst.addBack(1); lst.addBack(2);
    assert(lst.remove(2) == true);
    int e[] = {1};
    checkList(lst, e, 1);
    assert(lst.head == lst.tail);
    assert(lst.head->prev == NULL && lst.head->next == NULL);
   }
  // [1,2] -> [2]
   {
    IntList lst;
    lst.addBack(1); lst.addBack(2);
    assert(lst.remove(1) == true);
    int e[] = {2};
    checkList(lst, e, 1);
    assert(lst.head == lst.tail);
    assert(lst.tail->prev == NULL && lst.tail->next == NULL);
   }
 }

  void testRemoveToEmptyThenAgain() {
    IntList lst;
    lst.addBack(7); lst.addBack(7); // 7,7
    assert(lst.remove(7) == true);  // -> 7
    int e1[] = {7};
    checkList(lst, e1, 1);
    assert(lst.remove(7) == true);  // -> empty
    assert(lst.getSize() == 0);
    assert(lst.head == NULL && lst.tail == NULL);

    // again
    assert(lst.remove(7) == false);
    assert(lst.getSize() == 0);
    assert(lst.head == NULL && lst.tail == NULL);
  }

  void testRemoveNotFoundKeepsStructure() {
    IntList lst;
    lst.addBack(1); lst.addBack(2); lst.addBack(4); // 1,2,4
    int before[] = {1,2,4};
    checkList(lst, before, 3);
    assert(lst.remove(3) == false);                 // 3 not exist
    int after[] = {1,2,4};
    checkList(lst, after, 3);                       // verify structure
  }

  void run_all() {
	  testDefCtor();
	  testAddFront();
	  testAddBack();
	  testMixedAddAndLinks();
	  testIndexAndFind();
	  testRemoveVariants();
	  testAssignOp();
	  testCopyCtor();
	  testSelfAssignNonEmpty();
	  testAssignEmptyToNonEmpty();
	  testAssignNonEmptyToEmpty();
	  //testCopyCtorEmptyAndScope();
	  //testChainedAssign();
	  testRemoveFirstOccurrenceOnly();
	  testRemoveLen2Edges();
	  testRemoveToEmptyThenAgain();
	  testRemoveNotFoundKeepsStructure();

  }

  
};

int main(void) {
  Tester t;
  t.run_all();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
