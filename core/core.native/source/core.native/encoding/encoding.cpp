//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#define USELESS_ENCODING_SOURCE
#include <unordered_map>
#include <memory>
#if ( _WIN32 || _WIN64 )
#include <windows.h>
#elif __GNUC__
#endif
#include "encoding.h"

namespace useless
{
	const encoding& encoding::get( unsigned int codepage )
	{
		static std::unordered_map<unsigned int, std::shared_ptr<encoding>> s_map;
		auto it = s_map.find( codepage );
		if( it != s_map.end() )
		{
			return *( it->second );
		}

		std::shared_ptr<encoding> encoding( new encoding( codepage ) );
		s_map.insert( std::make_pair( codepage, encoding ) );
		return *encoding;
	}

	const encoding& encoding::default()
	{
		return encoding::get( CodePage::Default );
	}

	const encoding& encoding::utf8()
	{
		return encoding::get( CodePage::UTF8 );
	}

	void encoding::convert( const encoding& src, const encoding& dst, const string_ansi& input, string_ansi& output )
	{
		output = dst.from_wide( src.to_wide( input ) );
	}

	string_ansi encoding::convert( const encoding& src, const encoding& dst, const string_ansi& input )
	{
		return dst.from_wide( src.to_wide( input ) );
	}

	void encoding::convert( const encoding& src, const string_ansi& input, string_wide& output )
	{
		output = src.to_wide( input );
	}

	string_wide encoding::convert( const encoding& src, const string_ansi& input )
	{
		return src.to_wide( input );
	}

	void encoding::convert( const encoding& dst, const string_wide& input, string_ansi& output )
	{
		output = dst.from_wide( input );
	}

	string_ansi encoding::convert( const encoding& dst, const string_wide& input )
	{
		return dst.from_wide( input );
	}

	bool encoding::operator == ( const encoding& other ) const
	{
		return ( m_codepage == other.m_codepage );
	}

	bool encoding::operator != ( const encoding& other ) const
	{
		return ( m_codepage != other.m_codepage );
	}

	encoding::encoding( unsigned int codepage )
		: m_codepage( codepage )
	{
	}

	encoding::encoding( const encoding& other )
		: m_codepage( other.m_codepage )
	{

	}

	const encoding& encoding::operator=( const encoding& other )
	{
		m_codepage = other.m_codepage;
		return *this;
	}

	void encoding::from_wide( const string_wide& input, string_ansi& output ) const
	{
		int count = ::WideCharToMultiByte( m_codepage, 0, &input[ 0 ], static_cast<int>( input.length() ), 0, 0, 0, 0 );
		if( count > 0 )
		{
			output.resize( count );
			::WideCharToMultiByte( m_codepage, 0, &input[ 0 ], static_cast<int>( input.length() ), &output[ 0 ], count, 0, 0 );
		}
	}

	string_ansi encoding::from_wide( const string_wide& input ) const
	{
		string_ansi temp;
		from_wide( input, temp );
		return temp;
	}

	void encoding::to_wide( const string_ansi& input, string_wide& output ) const
	{
		int count = ::MultiByteToWideChar( m_codepage, 0, &input[ 0 ], static_cast<int>( input.length() ), 0, 0 );
		if( count > 0 )
		{
			output.resize( count );
			::MultiByteToWideChar( m_codepage, 0, &input[ 0 ], static_cast<int>( input.length() ), &output[ 0 ], count );
		}
	}

	string_wide encoding::to_wide( const string_ansi& input ) const
	{
		string_wide temp;
		to_wide( input, temp );
		return temp;
	}
}