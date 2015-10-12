//
// Copyright (c) 2015. Lee eui jong.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_MATH_USELESS_API_INCLUDED
#define USELESS_CORE_NATIVE_MATH_USELESS_API_INCLUDED

#include <boost/config.hpp>

#ifdef USELESS_DLL
#	ifdef CORE_MATH_EXPORT
#		define CORE_MATH_DECL BOOST_SYMBOL_EXPORT
#	else
#		define CORE_MATH_DECL BOOST_SYMBOL_IMPORT
#	endif
#else
#	define CORE_MATH_DECL
#endif

#if defined( _MSC_VER ) || defined( __BORLANDC__ )
#	if !defined( USELESS_MATH_SOURCE )
#		pragma comment( lib, "math.lib" )
#	endif
#endif

#endif USELESS_CORE_NATIVE_MATH_USELESS_API_INCLUDED