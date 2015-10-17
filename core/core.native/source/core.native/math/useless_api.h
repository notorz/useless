//
// Copyright (c) 2015. Lee eui jong.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_MATH_USELESS_API_INCLUDED
#define USELESS_CORE_NATIVE_MATH_USELESS_API_INCLUDED

#ifdef USELESS_DLL
#	ifdef CORE_MATH_EXPORT
#		define Core_API __declspec(dllexport)
#	else
#		define Core_API __declspec(dllimport)
#	endif
#else
#	define Core_API
#endif

#endif USELESS_CORE_NATIVE_MATH_USELESS_API_INCLUDED