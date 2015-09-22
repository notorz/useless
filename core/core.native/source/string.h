#pragma once

#include "string/string.h"

namespace useless
{
	typedef basic_string<char> string_ansi;
	typedef basic_string<wchar_t> string_wide;

#ifdef UNICODE
	typedef string_wide string;
#else
	typedef string_ansi string;
#endif
}