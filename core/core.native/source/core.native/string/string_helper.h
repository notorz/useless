//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_STRING_STRING_HELPER_INCLUDED
#define USELESS_CORE_NATIVE_STRING_STRING_HELPER_INCLUDED

#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <locale>
#include <boost/cstdint.hpp>

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
        static int64_t parse_int64( const C* value );
        static uint64_t parse_uint64( const char* value );
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
			return std::strlen( value );
		}

		static const char* contains( const char* value1, const char* value2 )
		{
			return std::strstr( value1, value2 );
		}

		static int compare( const char* value1, const char* value2 )
		{
			return std::strcmp( value1, value2 );
		}

		static int compare_no_case( const char* value1, const char* value2 )
		{
#if ( _WIN32 || _WIN64 )
			return ::_stricmp( value1, value2 );
#elif __GNUC__
            return ::strcasecmp( value1, value2 );
#endif
		}

		static int compare_no_case( const char* value1, const char* value2, size_t length )
		{
#if ( _WIN32 || _WIN64 )
			return ::_strnicmp( value1, value2, length );
#elif __GNUC__
            return ::strncasecmp( value1, value2, length );
#endif
		}

		static int parse_int( const char* value )
		{
			return std::atoi( value );
		}

		static unsigned int parse_uint( const char* value )
		{
			return static_cast<unsigned int>( std::strtoul( value, nullptr, 10 ) );
		}

		static int64_t parse_int64( const char* value )
		{
			return std::atoll( value );
		}

		static uint64_t parse_uint64( const char* value )
		{
			return std::strtoull( value, nullptr, 10 );
		}

		static float parse_float( const char* value )
		{
			return std::strtof( value, nullptr );
		}

		static double parse_double( const char* value )
		{
			return std::atof( value );
		}

		static bool parse_bool( const char* value )
		{
#if ( _WIN32 || _WIN64 )
			return ::_stricmp( value, "true" ) == 0;
#elif __GNUC__
            return ::strcasecmp( value, "true" ) == 0;
#endif
		}

		static bool is_alpha( char value )
		{
			return std::isalpha( value, std::locale() ) != 0;
		}

		static bool is_alpha_number( char value )
		{
			return std::isalnum( value, std::locale() ) != 0;
		}

		static void format_helper( const char* fmt, va_list marker, char* output, int count )
		{
            ::vsnprintf( &output[ 0 ], count, fmt, marker );
		}
	};

	template<>
	class string_helper<wchar_t>
	{
	public:
		static size_t length( const wchar_t* value )
		{
			return std::wcslen( value );
		}

		static const wchar_t* contains( const wchar_t* value1, const wchar_t* value2 )
		{
			return std::wcsstr( value1, value2 );
		}

		static int compare( const wchar_t* value1, const wchar_t* value2 )
		{
			return std::wcscmp( value1, value2 );
		}

		static int compare_no_case( const wchar_t* value1, const wchar_t* value2 )
		{
#if ( _WIN32 || _WIN64 )
			return ::_wcsicmp( value1, value2 );
#elif __GNUC__
            return ::wcscasecmp( value1, value2 );
#endif
		}

		static int compare_no_case( const wchar_t* value1, const wchar_t* value2, size_t length )
		{
#if ( _WIN32 || _WIN64 )
			return ::_wcsnicmp( value1, value2, length );
#elif __GNUC__
            return ::wcsncasecmp( value1, value2, length );
#endif
		}

		static int parse_int( const wchar_t* value )
		{
			return static_cast<int>( std::wcstol( value, nullptr, 10 ) );
		}

		static unsigned int parse_uint( const wchar_t* value )
		{
			return static_cast<unsigned int>( std::wcstoul( value, nullptr, 10 ) );
		}

		static int64_t parse_int64( const wchar_t* value )
		{
			return std::wcstoll( value, nullptr, 10 );
		}

		static uint64_t parse_uint64( const wchar_t* value )
		{
			return std::wcstoull( value, nullptr, 10 );
		}

		static float parse_float( const wchar_t* value )
		{
			return std::wcstof( value, nullptr );
		}

		static double parse_double( const wchar_t* value )
		{
			return std::wcstod( value, nullptr );
		}

		static bool parse_bool( const wchar_t* value )
		{
#if ( _WIN32 || _WIN64 )
			return ::_wcsicmp( value, L"true" ) == 0;
#elif __GNUC__
            return ::wcscasecmp( value, L"true" ) == 0;
#endif
		}

		static bool is_alpha( wchar_t value )
		{
			return std::isalpha( value, std::locale() ) != 0;
		}

		static bool is_alpha_number( wchar_t value )
		{
			return std::isalnum( value, std::locale() ) != 0;
		}

		static void format_helper( const wchar_t* fmt, va_list marker, wchar_t* output, int count )
		{
			::vswprintf( &output[ 0 ], count, fmt, marker );
		}
	};
}

#endif //USELESS_CORE_NATIVE_STRING_STRING_HELPER_INCLUDED