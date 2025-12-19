#include <cstdlib>
#include <sstream>
#include <string>
#include <iostream>

class Expression {
	public:
		virtual ~Expression() {}
		virtual std::string toString() const = 0;
		virtual long evaluate() const = 0;
};

class NumExpression : public Expression {
	private:
		long value;

	public:
		explicit NumExpression(long v) : value(v) {}
		
		virtual std::string toString() const {
			std::ostringstream string_stream;
			string_stream << value;
			return string_stream.str();
		}

		virtual long evaluate() const {
			return value;
		}
};

class Operation_expression : public Expression {
	protected:
		const char * op;
		Expression * lhs;
		Expression * rhs;

	public:
		Operation_expression(const char * op, Expression * lhs, Expression * rhs) 
			: op(op), lhs(lhs), rhs(rhs) {}

		virtual ~Operation_expression() {
			delete lhs;
			delete rhs;
		}

		virtual std::string toString() const {
			std::ostringstream string_stream;
			string_stream << "(" << lhs->toString() << " " << *op << " " << rhs->toString() << ")";
			return string_stream.str();
		}
};

class PlusExpression : public Operation_expression {
	public:
		PlusExpression(Expression * lhs, Expression * rhs) 
			: Operation_expression("+", lhs, rhs) {}

		virtual long evaluate() const {
			return lhs->evaluate() + rhs->evaluate();
		}
};

class MinusExpression : public Operation_expression {
	public:
		MinusExpression(Expression * lhs, Expression * rhs)
			: Operation_expression("-", lhs, rhs) {}

		virtual long evaluate() const {
			return lhs->evaluate() - rhs->evaluate();
		}
};

class TimesExpression : public Operation_expression {
	public:
		TimesExpression(Expression * lhs, Expression * rhs)
			: Operation_expression("*", lhs, rhs) {}

		virtual long evaluate() const {
			return lhs->evaluate() * rhs->evaluate();
		}
};

class DivExpression : public Operation_expression {
	public:
		DivExpression(Expression * lhs, Expression * rhs)
			: Operation_expression("/", lhs, rhs) {}

		virtual long evaluate() const {
			long denominator = rhs->evaluate();
			if (denominator == 0) {
				std::cerr << "You cannot divide a num by 0!\n";
				return 0;
			}
			return lhs->evaluate() / denominator;
		}
};

