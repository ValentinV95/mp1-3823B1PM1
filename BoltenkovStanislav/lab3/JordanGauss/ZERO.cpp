#include "ZERO.h"

static const double eps_double = 1e-14;
static const float eps_float = 1e-6;

bool operator==(const double& a, const ZERO&)
{
	return abs(a) < eps_double;
}

bool operator!=(const double& a, const ZERO&)
{
	return abs(a) > eps_double;
}

bool operator==(const float& a, const ZERO&)
{
	return abs(a) < eps_float;
}

bool operator!=(const float& a, const ZERO&)
{
	return abs(a) > eps_float;
}

bool operator==(const longFraction& a, const ZERO&)
{
	return abs(a) == longFraction(0, 0, 1);
}

bool operator!=(const longFraction& a, const ZERO&)
{
	return abs(a) != longFraction(0, 0, 1);
}