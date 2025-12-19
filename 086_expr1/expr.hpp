#include <cstdlib>
#include <sstream>
#include <string>

class Expression {
	public:
		virtual ~Expression() {}
		virtual std::string toString() const = 0;
};

class NumExpression : public Expression {
	private:
		long value;

	public:
		NumExpression(long v) : value(v) {}
		
		virtual std::string toString() const {
			std::ostringstream string_stream;
			string_stream << value;
			return string_stream.str();
		}
};

class PlusExpression : public Expression {
	private:
		Expression * lhs;
		Expression * rhs;

	public:
		PlusExpression(Expression * l, Expression * r) : lhs(l), rhs(r) {}

	virtual ~PlusExpression() {
		delete lhs;
		delete rhs;
	}

	virtual std::string toString() const {
		return "(" + lhs->toString() + " + " + rhs->toString() + ")";
	}
};
