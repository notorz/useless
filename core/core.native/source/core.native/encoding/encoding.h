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
	namespace charset
	{
		enum type
		{
			system_default,
			
            ascii,
            utf8,
            
			korean,
			japanese,
			chinese_simplified,
			chinese_traditional,
		};
	}

	class CORE_ENCODING_DECL encoding
	{
	public:
        static const encoding& get( charset::type charset = charset::system_default );
        
        static const encoding& ascii();
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
		encoding( charset::type charset );
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
        charset::type m_charset;
        
#if ( _WIN32 || _WIN64 )
        unsigned int m_codepage;
#elif __GNUC__
        string_ansi m_name;
#endif
	};
}

#endif //USELESS_CORE_NATIVE_ENCODING_ENCODING_INCLUDED