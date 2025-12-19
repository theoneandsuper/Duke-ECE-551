#include "point.hpp"
#include <cmath>

void Point::move(double dx, double dy) {
	x += dx;
	y += dy;
}

double Point::distanceFrom(const Point & p) {
	double dx = x - p.x;
	double dy = y - p.y;
	return std::sqrt(dx * dx + dy * dy);
}
