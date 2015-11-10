//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#define USELESS_ENCODING_SOURCE
#include <unordered_map>
#include <memory>
#include <vector>
#if ( _WIN32 || _WIN64 )
#include <windows.h>
#elif __GNUC__
#include <boost/locale.hpp>
#endif
#include "encoding.h"

namespace std
{
    template<>
    class hash<useless::charset::type>
    {
    public:
        size_t operator()( const useless::charset::type& value ) const
        {
            return static_cast<std::size_t>( value );
        }
    };
}

namespace useless
{
    const encoding& encoding::get( charset::type charset )
	{
        static std::unordered_map<charset::type, std::shared_ptr<encoding>> s_map;
		auto it = s_map.find( charset );
		if( it != s_map.end() )
		{
			return *( it->second );
		}

		std::shared_ptr<encoding> encoding( new class encoding( charset ) );
		s_map.insert( std::make_pair( charset, encoding ) );
		return *encoding;
	}
    
    const encoding& encoding::ascii()
    {
        return encoding::get( charset::ASCII );
    }
    
    const encoding& encoding::utf8()
	{
        return encoding::get( charset::UTF8 );
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
		return ( m_charset == other.m_charset );
	}

	bool encoding::operator != ( const encoding& other ) const
	{
		return ( m_charset != other.m_charset );
	}

    encoding::encoding( charset::type charset )
		: m_charset( charset )
	{
#if ( _WIN32 || _WIN64 )
        switch( charset )
        {
            case charset::Default: m_codepage = CP_ACP; break;
            case charset::ASCII: m_codepage = 20127; break;
            case charset::UTF8: m_codepage = CP_UTF8; break;
            case charset::Korean: m_codepage = 949; break;
            case charset::Japanese: m_codepage = 932; break;
            case charset::ChineseSimplified: m_codepage = 936; break;
            case charset::ChineseTraditional: m_codepage = 950; break;
        }
#elif __GNUC__
        switch( charset )
        {
            case charset::Default: m_name = "*"; break;
            case charset::ASCII: m_name = "us-ascii"; break;
            case charset::UTF8: m_name = "utf-8"; break;
            case charset::Korean: m_name = "euc-kr"; break;
            case charset::Japanese: m_name = "euc-jp"; break;
            case charset::ChineseSimplified: m_name = "euc-cn"; break;
            case charset::ChineseTraditional: m_name = "euc-tw"; break;
        }
#endif
	}

	encoding::encoding( const encoding& other )
		: m_charset( other.m_charset )
	{

	}

	const encoding& encoding::operator=( const encoding& other )
	{
		m_charset = other.m_charset;
		return *this;
	}

	void encoding::from_wide( const string_wide& input, string_ansi& output ) const
	{
#if ( _WIN32 || _WIN64 )
		int count = ::WideCharToMultiByte( m_codepage, 0, &input[ 0 ], static_cast<int>( input.length() ), 0, 0, 0, 0 );
		if( count > 0 )
		{
			output.resize( count );
			::WideCharToMultiByte( m_codepage, 0, &input[ 0 ], static_cast<int>( input.length() ), &output[ 0 ], count, 0, 0 );
		}
#elif __GNUC__
        if( m_charset == charset::Default )
        {
            static boost::locale::generator s_gen;
            output = boost::locale::conv::from_utf<wchar_t>( input.buffer(), s_gen( m_name.buffer() ) );
        }
        else if( m_charset == charset::UTF8 )
        {
            output = boost::locale::conv::utf_to_utf<char>( input.buffer() );
        }
        else
        {
            output = boost::locale::conv::from_utf( input.buffer(), m_name.buffer() );
        }
#endif
	}

	string_ansi encoding::from_wide( const string_wide& input ) const
	{
		string_ansi temp;
		from_wide( input, temp );
		return temp;
	}

	void encoding::to_wide( const string_ansi& input, string_wide& output ) const
	{
#if ( _WIN32 || _WIN64 )
		int count = ::MultiByteToWideChar( m_codepage, 0, &input[ 0 ], static_cast<int>( input.length() ), 0, 0 );
		if( count > 0 )
		{
			output.resize( count );
			::MultiByteToWideChar( m_codepage, 0, &input[ 0 ], static_cast<int>( input.length() ), &output[ 0 ], count );
		}
#elif __GNUC__
        if( m_charset == charset::Default )
        {
            static boost::locale::generator s_gen;
            output = boost::locale::conv::to_utf<wchar_t>( input.buffer(), s_gen( m_name.buffer() ) );
        }
        else if( m_charset == charset::UTF8 )
        {
            output = boost::locale::conv::utf_to_utf<wchar_t>( input.buffer() );
        }
        else
        {
            output = boost::locale::conv::to_utf<wchar_t>( input.buffer(), m_name.buffer() );
        }
#endif
	}

	string_wide encoding::to_wide( const string_ansi& input ) const
	{
		string_wide temp;
		to_wide( input, temp );
		return temp;
	}
}