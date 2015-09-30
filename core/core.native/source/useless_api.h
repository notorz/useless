//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_USELESS_API_INCLUDED
#define USELESS_CORE_NATIVE_USELESS_API_INCLUDED

#ifdef USELESS_DLL
#ifdef CORE_EXPORT
#define Core_API __declspec(dllexport)
#else
#define Core_API __declspec(dllimport)
#endif
#else
#define Core_API
#endif

#endif USELESS_CORE_NATIVE_USELESS_API_INCLUDED