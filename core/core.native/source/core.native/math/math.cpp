#include "math.h"

namespace useless
{
	double math::PI = 3.14159265;

	double math::RadianToDgree(double radian)
	{
		return radian * 180.0 / math::PI;
	}

	double math::DgreeToRadian(double degree)
	{
		return degree * math::PI / 180.0;
	}
}