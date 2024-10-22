#include "FloatUtils.hpp"
#include <limits>
#include <cmath>

bool FloatUtils::isAlmostZero(float x) {
	return std::fabs(x) < std::numeric_limits<float>::epsilon();
}