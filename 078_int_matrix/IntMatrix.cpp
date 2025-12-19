#include "IntMatrix.h"

IntMatrix::IntMatrix(){
	numRows = 0;
	numColumns = 0;
	rows = NULL;
}
IntMatrix::IntMatrix(int r, int c) {
	numRows = r;
	numColumns = c;
	rows = new IntArray *[numRows];
	for (int i = 0; i < numRows; i++) {
		rows[i] = new IntArray(numColumns);
	}
}
IntMatrix::IntMatrix(const IntMatrix & rhs)  {
	numRows = rhs.numRows;
	numColumns = rhs.numColumns;
	rows = new IntArray *[numRows];
	for (int i = 0; i < numRows; i++) {
		rows[i] = new IntArray(numColumns);
		*rows[i] = *rhs.rows[i];
	}
}
IntMatrix::~IntMatrix() {
	for (int i = 0; i < numRows; i++) {
		delete rows[i];
	}
	delete[] rows;
}

IntMatrix &IntMatrix::operator=(const IntMatrix & rhs) {
	if (this != &rhs) {
		IntArray ** temp_array = new IntArray *[rhs.numRows];
		for (int i = 0; i < rhs.numRows; i++) {
			temp_array[i] = new IntArray(rhs.numColumns);
			*temp_array[i] = *rhs.rows[i];
		}
		for (int i = 0; i < numRows; i++) {
			delete rows[i];
		}
		delete[] rows;
		numRows = rhs.numRows;
		numColumns = rhs.numColumns;
		rows = temp_array;
	}
	return *this;
}
int IntMatrix::getRows() const {
	return numRows;
}
int IntMatrix::getColumns() const {
	return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
	assert(index >= 0 && index < numRows);
	return *(rows[index]);
}
IntArray & IntMatrix::operator[](int index){
	assert(index >= 0 && index < numRows);
	return *(rows[index]);
}



bool IntMatrix::operator==(const IntMatrix & rhs) const {
	if (numRows != rhs.numRows || numColumns != rhs.numColumns) {
		return false;
	}
	for (int i = 0; i < numRows; i++) {
		if (*(rows[i]) != *(rhs.rows[i])) {
			return false;
		}
	}
	return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
	assert(numRows == rhs.numRows && numColumns == rhs.numColumns);

	IntMatrix answer(numRows, numColumns);
	for (int r = 0; r < numRows; r++) {
		for (int c = 0; c < numColumns; c++) {
			(*answer.rows[r])[c] = (*rows[r])[c] + (*rhs.rows[r])[c];
		}
	}
	return answer;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
	s << "[ ";
	for (int i = 0; i < rhs.getRows(); i++) {
		s << rhs[i];
		if (i != rhs.getRows() - 1) {
			s << ",\n";
		}
	}
	s << " ]";
	return s;
}
