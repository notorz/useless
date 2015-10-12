
#ifndef USELESS_CORE_NATIVE_MATH_MATH_INCLUDED
#define USELESS_CORE_NATIVE_MATH_MATH_INCLUDED

#include "core.native/math/definitions.h"

namespace useless
{
	class CORE_MATH_DECL math
	{
	public:
		static double PI;

		static double rad_to_deg(double radian);
		static double deg_to_rad(double degree);
	};
}

#endif USELESS_CORE_NATIVE_MATH_MATH_INCLUDED