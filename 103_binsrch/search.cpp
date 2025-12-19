#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low >= high) {
    return low;
  }

  int lo = low;
  int hi = high;

  while (lo < hi) {
    int mid = lo + (hi - lo) / 2;
    int val = f->invoke(mid);

    if (val <= 0) {
      lo = mid + 1;
    }
    else {
      hi = mid;
    }
  }

  int candidate = lo - 1;

  if (candidate < low) {
    return low;
  }

  if (candidate >= high) {
    candidate = high - 1;
  }

  return candidate;
}

