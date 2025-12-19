#include "circle.hpp"
#include <cmath>
#include <algorithm>

void Circle::move(double dx, double dy) {
	center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & other) const{
	const double d = center.distanceFrom(other.center);
	const double r1 = radius;
	const double r2 = other.radius;

	if (d >= r1 + r2) {
		return 0.0;
	}

	if (d <= std::fabs(r1 - r2)) {
		const double rMin = std::min(r1, r2);
		return M_PI * rMin * rMin;
	}

	const double alpha = std::acos((d * d + r1 * r1 - r2 * r2) / (2.0 * d * r1));
	const double beta  = std::acos((d * d + r2 * r2 - r1 * r1) / (2.0 * d * r2));
	const double term  = 0.5 * std::sqrt((-d + r1 + r2) * (d + r1 - r2) * (d - r1 + r2) * (d + r1 + r2));
	return r1 * r1 * alpha + r2 * r2 * beta - term;
}	
