#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "point.hpp"

class Circle {
	private:
		Point center;
		const double radius;

	public:
		Circle(const Point & c, double r) : center(c), radius(r) {}
		double intersectionArea(const Circle & other) const;
		void move(double dx, double dy);
};

#endif
