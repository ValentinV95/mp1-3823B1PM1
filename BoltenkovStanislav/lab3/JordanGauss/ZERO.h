#pragma once
#include <cmath>
#include "LongFraction.h"

class ZERO
{

};

static const ZERO __ZERO;

bool operator==(const double& a, const ZERO&);
bool operator!=(const double& a, const ZERO&);

bool operator==(const float& a, const ZERO&);
bool operator!=(const float& a, const ZERO&);

bool operator==(const longFraction& a, const ZERO&);
bool operator!=(const longFraction& a, const ZERO&);