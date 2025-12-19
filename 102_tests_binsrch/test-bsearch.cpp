#include <cmath>
#include <iostream>
#include <cstdlib>
#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high);

class counted_int_fn : public Function<int, int> {
 protected:
  unsigned remaining_calls;
  Function<int, int> * base_fn;
  const char * message;

 public:
  counted_int_fn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining_calls(n),
      base_fn(fn),
      message(m) {}

  virtual int invoke(int arg) {
    if (remaining_calls == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", message);
      exit(EXIT_FAILURE);
    }
    remaining_calls--;
    return base_fn->invoke(arg);
  }
};

// sin function
class sin_function : public Function<int, int> {
 public:
  virtual int invoke(int arg) {
    return 10000000 * (sin(arg / 100000.0) - 0.5);
  }
};

// constant -10
class neg_function : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return -10; }
};

// constant 3
class pos_function : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 3; }
};

// monotone increasing f(x)=2x+2
class mono_incrs_function : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 2 * arg + 2; }
};

// monotone decreasing f(x)=-x (extra robustness)
class mono_dcrs_function : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return -arg; }
};

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * message) {
  int max_invocations;

  if (high > low) {
    max_invocations = log(high - low) / log(2) + 1;
  }
  else {
    max_invocations = 1;
  }

  counted_int_fn * counted_fn = new counted_int_fn(max_invocations, f, message);

  int result = binarySearchForZero(counted_fn, low, high);

  if (result != expected_ans) {
    fprintf(stderr, "The result of function %s is wrong!\n", message);
    exit(EXIT_FAILURE);
  }
}

struct test_case {
  Function<int, int> * f;
  int low;
  int high;
  int expected_ans;
  const char * message;
};

int main() {
  sin_function sin_f;
  neg_function neg_f;
  pos_function pos_f;
  mono_incrs_function mono_inc_f;
  mono_dcrs_function mono_dec_f;

  test_case cases[] = {
    // sin — different interval, still contains zero at 52359
    {&sin_f, 1000, 200000, 52359, "Sin new interval"},

    // negative constant (all negative) — expected = high - 1
    {&neg_f, -50, 250, 249, "Neg in [-50,250)"},
    {&neg_f, 20, 300, 299, "Neg in [20,300)"},
    {&neg_f, -500, -200, -201, "Neg in [-500,-200)"},
    {&neg_f, 5, 5, 5, "Neg in (5,5)"},

    // positive constant (all positive) — expected = low
    {&pos_f, -20, 400, -20, "Pos in [-20,400)"},
    {&pos_f, 50, 500, 50, "Pos in [50,500)"},
    {&pos_f, -200, -50, -200, "Pos in [-200,-50)"},
    {&pos_f, 8, 8, 8, "Pos in (8,8)"},

    // monotone increasing f(x)=2x+2
    // zero between -1 and 0
    {&mono_inc_f, -200, 20, -1, "MIF includes zero"},
    {&mono_inc_f, 5, 200, 5, "MIF all positive"},
    {&mono_inc_f, -300, -20, -21, "MIF all negative"},
    {&mono_inc_f, 12, 12, 12, "MIF empty interval"},

    // monotone decreasing f(x)=-x (robustness; not required by README)
    {&mono_dec_f, -200, 200, 0, "MDF mixed"},
    {&mono_dec_f, 1, 600, 599, "MDF all negative outputs"},
    {&mono_dec_f, -500, -100, -500, "MDF all positive outputs"},
    {&mono_dec_f, 3, 3, 3, "MDF empty interval"},
  };

  int num_cases = sizeof(cases) / sizeof(cases[0]);
  for (int i = 0; i < num_cases; i++) {
    check(cases[i].f,
          cases[i].low,
          cases[i].high,
          cases[i].expected_ans,
          cases[i].message);
  }

  return EXIT_SUCCESS;
}

