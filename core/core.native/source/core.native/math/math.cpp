//
// Copyright (c) 2015. Lee eui jong.
//
// Distributed under the MIT License.
//

#include "math.h"

namespace useless
{
	double math::PI = 3.14159265;

	double math::rad_to_deg(double radian)
	{
		return radian * 180.0 / math::PI;
	}

	double math::deg_to_rad(double degree)
	{
		return degree * math::PI / 180.0;
	}
}