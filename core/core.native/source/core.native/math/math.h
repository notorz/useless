
#ifndef USELESS_CORE_NATIVE_MATH_MATH_INCLUDED
#define USELESS_CORE_NATIVE_MATH_MATH_INCLUDED

#include "useless_api.h"

namespace useless
{
	class Core_API math
	{
	public:
		static double PI;

		static double RadianToDgree(double radian);
		static double DgreeToRadian(double degree);
	};
}

#endif USELESS_CORE_NATIVE_MATH_MATH_INCLUDED