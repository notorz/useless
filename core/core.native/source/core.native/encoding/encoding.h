//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_ENCODING_ENCODING_INCLUDED
#define USELESS_CORE_NATIVE_ENCODING_ENCODING_INCLUDED

#include "core.native/string.h"
#include "definitions.h"

namespace useless
{
	namespace CodePage
	{
		enum Type
		{
			Default = 0,
			UTF8 = 65001,

			Korean = 949,
			Japanese = 932,
			ChineseSimplified = 936,
			ChineseTraditional = 950
		};
	}

	class CORE_ENCODING_DECL encoding
	{
	public:
		static const encoding& get( unsigned int codepage );

		static const encoding& default();
		static const encoding& utf8();

		// mbs -> mbs
		static void convert( const encoding& src, const encoding& dst, const string_ansi& input, string_ansi& output );
		static string_ansi convert( const encoding& src, const encoding& dst, const string_ansi& input );

		// mbs -> wcs
		static void convert( const encoding& src, const string_ansi& input, string_wide& output );
		static string_wide convert( const encoding& src, const string_ansi& input );

		// wcs -> mbs
		static void convert( const encoding& dst, const string_wide& input, string_ansi& output );
		static string_ansi convert( const encoding& dst, const string_wide& input );

	private:
		encoding( unsigned int codepage );
		encoding( const encoding& other );
		const encoding& operator=( const encoding& other );

	public:
		bool operator == ( const encoding& other ) const;
		bool operator != ( const encoding& other ) const;

		void from_wide( const string_wide& input, string_ansi& output ) const;
		string_ansi from_wide( const string_wide& input ) const;

		void to_wide( const string_ansi& input, string_wide& output ) const;
		string_wide to_wide( const string_ansi& input ) const;

	private:
		unsigned int m_codepage;
	};
}

#endif USELESS_CORE_NATIVE_ENCODING_ENCODING_INCLUDED