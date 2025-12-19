#include <vector>
#include <ostream>
#include <cstddef>
#include <iostream>

template <typename numT>
class Polynomial {
	private:
		std::vector<numT> coefficient;

		void normalize() {
			while (!coefficient.empty() && coefficient.back() == numT()) {
				coefficient.pop_back();
			}
		}

	public:
		Polynomial() : coefficient() {}

		void addTerm(const numT & c, unsigned p) {
			if (c == numT()) {
				 normalize();
				 return;
			}
			if (p >= coefficient.size()) {
				coefficient.resize(p + 1, numT());
			}
			coefficient[p] = coefficient[p] + c;
			normalize();
		}

		Polynomial operator-() const {
			Polynomial result(*this);
			for (std::size_t i = 0; i < result.coefficient.size(); i++) {
				result.coefficient[i] = -result.coefficient[i];
			}
			result.normalize();
			return result;
		}

		Polynomial operator+(const Polynomial & rhs) const {
			Polynomial result;
			std::size_t max_size = (coefficient.size() > rhs.coefficient.size()) ? coefficient.size() : rhs.coefficient.size();
			result.coefficient.assign(max_size, numT());

			for (std::size_t i = 0; i < max_size; i++) {
				numT a = (i < coefficient.size()) ? coefficient[i] : numT();
				numT b = (i < rhs.coefficient.size()) ? rhs.coefficient[i] : numT();
				result.coefficient[i] = a + b;
			}
			result.normalize();
			return result;
		}

		Polynomial operator-(const Polynomial & rhs) const {
			return *this + (-rhs);
		}

		Polynomial operator*(const numT & n) const {
			Polynomial result(*this);
			if (n == numT()) {
				result.coefficient.clear();
				return result;
    			}	
			for (std::size_t i = 0; i < result.coefficient.size(); i++) {
				result.coefficient[i] = result.coefficient[i] * n;
			}
			result.normalize();
			return result;
		}

		Polynomial operator*(const Polynomial & rhs) const {
			Polynomial result;
			if (coefficient.empty() || rhs.coefficient.empty()) {
				return result;
			}

			std::size_t result_size = coefficient.size() + rhs.coefficient.size() - 1;
			result.coefficient.assign(result_size, numT());

			for (std::size_t i = 0; i < coefficient.size(); i++) {
				for (std::size_t j = 0; j < rhs.coefficient.size(); j++) {
					result.coefficient[i + j] += coefficient[i] * rhs.coefficient[j];
				}
			}
			result.normalize();
			return result;
		}

		bool operator==(const Polynomial & rhs) const {
			std::size_t max_size = (coefficient.size() > rhs.coefficient.size()) ? coefficient.size() : rhs.coefficient.size();
			
			for (std::size_t i = 0; i < max_size; i++) {
				numT a = (i < coefficient.size()) ? coefficient[i] : numT();
				numT b = (i < rhs.coefficient.size()) ? rhs.coefficient[i] : numT();
				if (!(a == b)) {
					return false;
				}
			}
			return true;
		}

		bool operator!=(const Polynomial & rhs) const {
			return !(*this == rhs);
		}

		Polynomial & operator+=(const Polynomial & rhs) {
			*this = *this + rhs;
			return *this;
		}

		Polynomial & operator-=(const Polynomial & rhs) {
			*this = *this - rhs;
			return *this;
		}

		Polynomial & operator*=(const Polynomial & rhs) {
			*this = *this * rhs;
			return *this;
		}

		Polynomial & operator*=(const numT & rhs) {
			*this = *this * rhs;
			return *this;
		}

		template <typename N>
		friend std::ostream & operator<<(std::ostream & os, const Polynomial<N> & p);
};

template <typename numT>
std::ostream & operator<<(std::ostream & os, const Polynomial<numT> & p) {
	std::size_t size = p.coefficient.size();
	std::size_t highest = size;
	while (highest > 0) {
			if (!(p.coefficient[highest - 1] == numT())) {
			break;
		}
		highest--;
	}

	if (highest == 0) {
		os << numT();
		return os;
	}

	bool first_term = true;

	for (std::size_t index= highest; index > 0; --index) {
		std::size_t i = index - 1;
		const numT & c = p.coefficient[i];

		if (c == numT()) {
			continue;
		}

		if (!first_term) {
			os << " + ";
		}

		os << c << "*x^" << i;

		first_term = false;
	}

	return os;
}

