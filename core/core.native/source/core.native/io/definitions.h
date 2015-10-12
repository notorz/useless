//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_IO_DEFINITIONS_INCLUDED
#define USELESS_CORE_NATIVE_IO_DEFINITIONS_INCLUDED

#include <boost/config.hpp>

#ifdef USELESS_DLL
#	ifdef CORE_IO_EXPORT
#		define CORE_IO_DECL BOOST_SYMBOL_EXPORT
#	else
#		define CORE_IO_DECL BOOST_SYMBOL_IMPORT
#	endif
#else
#	define CORE_IO_DECL
#endif

#if defined( _MSC_VER ) || defined( __BORLANDC__ )
#	if !defined( USELESS_IO_SOURCE )
#		pragma comment( lib, "io.lib" )
#	endif
#endif

#endif USELESS_CORE_NATIVE_IO_DEFINITIONS_INCLUDED