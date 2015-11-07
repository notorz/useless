//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_STRING_INCLUDED
#define USELESS_CORE_NATIVE_STRING_INCLUDED

#include "string/string.h"

namespace useless
{
	typedef basic_string<char, std::allocator<char>> string_ansi;
	typedef basic_string<wchar_t, std::allocator<wchar_t>> string_wide;

#ifdef UNICODE
	typedef string_wide string;
#else
	typedef string_ansi string;
#endif
}

#endif //USELESS_CORE_NATIVE_STRING_INCLUDED