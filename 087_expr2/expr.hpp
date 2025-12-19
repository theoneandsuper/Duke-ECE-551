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
		explicit NumExpression(long v) : value(v) {}
		
		virtual std::string toString() const {
			std::ostringstream string_stream;
			string_stream << value;
			return string_stream.str();
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
};

class MinusExpression : public Operation_expression {
	public:
		MinusExpression(Expression * lhs, Expression * rhs)
			: Operation_expression("-", lhs, rhs) {}
};

class TimesExpression : public Operation_expression {
	public:
		TimesExpression(Expression * lhs, Expression * rhs)
			: Operation_expression("*", lhs, rhs) {}
};

class DivExpression : public Operation_expression {
	public:
		DivExpression(Expression * lhs, Expression * rhs)
			: Operation_expression("/", lhs, rhs) {}
};

