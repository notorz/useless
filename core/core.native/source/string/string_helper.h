//
// Copyright (c) 2015. notorz.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_STRING_STRING_HELPER_INCLUDED
#define USELESS_CORE_NATIVE_STRING_STRING_HELPER_INCLUDED

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

namespace useless
{
	template<typename C>
	class string_helper
	{
	public:
		static unsigned int length( const C* value );
		static const C* contains( const C* value1, const C* value2 );
		static int compare( const C* value1, const C* value2 );
		static int compare_no_case( const C* value1, const C* value2 );
		static int compare_no_case( const C* value1, const C* value2, unsigned int length );
		static int parse_int( const C* value );
		static unsigned int parse_uint( const C* value );
		static float parse_float( const C* value );
		static double parse_double( const C* value );
		static bool parse_bool( const char* value );
		static bool is_alpha( C value );
		static bool is_alpha_number( C value );
		static void format_helper( const char* fmt, const va_list& marker, C* output );
	};

	template<>
	class string_helper<char>
	{
	public:
		static size_t length( const char* value )
		{
			return ::strlen( value );
		}

		static const char* contains( const char* value1, const char* value2 )
		{
			return ::strstr( value1, value2 );
		}

		static int compare( const char* value1, const char* value2 )
		{
			return ::strcmp( value1, value2 );
		}

		static int compare_no_case( const char* value1, const char* value2 )
		{
			return ::_stricmp( value1, value2 );
		}

		static int compare_no_case( const char* value1, const char* value2, unsigned int length )
		{
			return ::_strnicmp( value1, value2, length );
		}

		static int parse_int( const char* value )
		{
			return ::atoi( value );
		}

		static unsigned int parse_uint( const char* value )
		{
			return static_cast<unsigned int>( ::strtoul( value, NULL, 10 ) );
		}

		static __int64 parse_int64( const char* value )
		{
			return ::_atoi64( value );
		}

		static __int64 parseuint64( const char* value )
		{
			return ::_strtoui64( value, NULL, 10 );
		}

		static float parse_float( const char* value )
		{
			return static_cast<float>( ::atof( value ) );
		}

		static double parse_double( const char* value )
		{
			return ::atof( value );
		}

		static bool parse_bool( const char* value )
		{
			return ::_stricmp( value, "TRUE" ) == 0;
		}

		static bool is_alpha( char value )
		{
			return ::isalpha( static_cast<int>( value ) ) != 0;
		}

		static bool is_alpha_number( char value )
		{
			return ::isalnum( static_cast<int>( value ) ) != 0;
		}

		static void format_helper( const char* fmt, const va_list& marker, char* output )
		{
			__declspec( thread ) static int len;
			len = ::_vscprintf( fmt, marker ) + 1;
			::vsprintf_s( &output[ 0 ], len, fmt, marker );
			output[ len ] = '\0';
		}
	};

	template<>
	class string_helper<wchar_t>
	{
	public:
		static size_t length( const wchar_t* value )
		{
			return ::wcslen( value );
		}

		static const wchar_t* contains( const wchar_t* value1, const wchar_t* value2 )
		{
			return ::wcsstr( value1, value2 );
		}

		static int compare( const wchar_t* value1, const wchar_t* value2 )
		{
			return ::wcscmp( value1, value2 );
		}

		static int compare_no_case( const wchar_t* value1, const wchar_t* value2 )
		{
			return ::_wcsicmp( value1, value2 );
		}

		static int compare_no_case( const wchar_t* value1, const wchar_t* value2, unsigned int length )
		{
			return ::_wcsnicmp( value1, value2, length );
		}

		static int parse_int( const wchar_t* value )
		{
			return ::_wtoi( value );
		}

		static unsigned int parse_uint( const wchar_t* value )
		{
			return static_cast<unsigned int>( ::wcstoul( value, NULL, 10 ) );
		}

		static __int64 parse_int64( const wchar_t* value )
		{
			return ::_wtoi64( value );
		}

		static unsigned __int64 parse_uint64( const wchar_t* value )
		{
			return ::_wcstoui64( value, NULL, 10 );
		}

		static float parse_float( const wchar_t* value )
		{
			return static_cast<float>( ::_wtof( value ) );
		}

		static double parse_double( const wchar_t* value )
		{
			return ::_wtof( value );
		}

		static bool parse_bool( const wchar_t* value )
		{
			return ::_wcsicmp( value, L"TRUE" ) == 0;
		}

		static bool is_alpha( wchar_t value )
		{
			return ::iswalpha( value ) != 0;
		}

		static bool is_alpha_number( wchar_t value )
		{
			return ::iswalnum( value ) != 0;
		}

		static void format_helper( const wchar_t* fmt, const va_list& marker, wchar_t* output )
		{
			__declspec( thread ) static int len;
			len = ::_vscwprintf( fmt, marker ) + 1;
			::vswprintf_s( &output[ 0 ], len, fmt, marker );
			output[ len ] = L'\0';
		}
	};
}

#endif USELESS_CORE_NATIVE_STRING_STRING_HELPER_INCLUDED