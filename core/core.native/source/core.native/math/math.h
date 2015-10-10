
#ifndef USELESS_CORE_NATIVE_MATH_MATH_INCLUDED
#define USELESS_CORE_NATIVE_MATH_MATH_INCLUDED

#include "useless_api.h"

namespace useless
{
	class Core_API math
	{
	public:
		static double PI;

		static double rad_to_deg(double radian);
		static double deg_to_rad(double degree);
	};
}

#endif USELESS_CORE_NATIVE_MATH_MATH_INCLUDED