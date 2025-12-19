#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>


//YOUR CODE GOES HERE!
template <typename T>
class Matrix {
 public:
  Matrix() : numRows(0), numColumns(0), rows() {}
  Matrix(int r, int c) : numRows(r), numColumns(c), rows(r, std::vector<T>(c, T())) {}
  Matrix(const Matrix & rhs)
      : numRows(rhs.numRows), numColumns(rhs.numColumns), rows(rhs.rows) {}

  Matrix & operator=(const Matrix & rhs) {
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = rhs.rows;
    return *this;
  }

  ~Matrix() {}

  int getRows() const { return numRows; }
  int getColumns() const { return numColumns; }

  const std::vector<T> & operator[](int index) const {
    assert(index >= 0 && index < numRows);
    return rows[index];
  }

  std::vector<T> & operator[](int index) {
    assert(index >= 0 && index < numRows);
    return rows[index];
  }

  bool operator==(const Matrix & rhs) const {
    if (numRows != rhs.numRows || numColumns != rhs.numColumns)
      return false;
    return rows == rhs.rows;
  }

  Matrix operator+(const Matrix & rhs) const {
    assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
    Matrix result(numRows, numColumns);
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        result.rows[i][j] = rows[i][j] + rhs.rows[i][j];
      }
    }
    return result;
  }

  friend std::ostream & operator<<(std::ostream & s, const Matrix & rhs) {
    s << "[ ";
    for (int i = 0; i < rhs.numRows; i++) {
      if (i != 0) s << ",\n";
      s << "{";
      for (int j = 0; j < rhs.numColumns; j++) {
        if (j != 0) s << ", ";
        s << rhs.rows[i][j];
      }
      s << "}";
    }
    s << " ]";
    return s;
  }

 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows; 
 };

#endif
