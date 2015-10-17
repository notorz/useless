//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#define USELESS_ENCODING_SOURCE
#include <unordered_map>
#include <memory>
#pragma warning( disable : 4100 )
#include <boost/thread.hpp>
#pragma warning( default : 4100 )
#include <boost/locale.hpp>
#include "encoding.h"

namespace useless
{
	const encoding& encoding::get( const string_ansi& charset )
	{
		static std::unordered_map<std::string, std::shared_ptr<encoding>> s_map;
		auto it = s_map.find( charset.buffer() );
		if( it != s_map.end() )
		{
			return *( it->second );
		}

		std::shared_ptr<encoding> encoding( new encoding( charset ) );
		s_map.insert( std::make_pair( charset.buffer(), encoding ) );
		return *encoding;
	}

	const encoding& encoding::default( )
	{
		return encoding::get( "" );
	}

	const encoding& encoding::ascii()
	{
		return encoding::get( "us-ascii" );
	}

	const encoding& encoding::utf8()
	{
		return encoding::get( "utf-8" );
	}

	const encoding& encoding::utf16()
	{
		return encoding::get( "utf-16le" );
	}

	const encoding& encoding::utf16_big_endian()
	{
		return encoding::get( "utf-16be" );
	}

	const encoding& encoding::utf32()
	{
		return encoding::get( "utf-32le" );
	}

	const encoding& encoding::utf32_big_endian()
	{
		return encoding::get( "utf-32be" );
	}

	void encoding::convert( const encoding& src, const encoding& dst, const string_ansi& input, string_ansi& output )
	{
		std::string temp = boost::locale::conv::to_utf<char>( input.buffer(), src.m_loc );
		output = boost::locale::conv::from_utf<char>( temp, dst.m_loc );
	}

	string_ansi encoding::convert( const encoding& src, const encoding& dst, const string_ansi& input )
	{
		std::string temp = boost::locale::conv::to_utf<char>( input.buffer(), src.m_loc );
		return boost::locale::conv::from_utf<char>( temp, dst.m_loc );
	}

	void encoding::convert( const encoding& src, const string_ansi& input, string_wide& output )
	{
		output = boost::locale::conv::to_utf<wchar_t>( input.buffer(), src.m_loc );
	}

	string_wide encoding::convert( const encoding& src, const string_ansi& input )
	{
		return boost::locale::conv::to_utf<wchar_t>( input.buffer(), src.m_loc );;
	}

	void encoding::convert( const encoding& dst, const string_wide& input, string_ansi& output )
	{
		output = boost::locale::conv::from_utf<wchar_t>( input.buffer(), dst.m_loc );
	}

	string_ansi encoding::convert( const encoding& dst, const string_wide& input )
	{
		return boost::locale::conv::from_utf<wchar_t>( input.buffer(), dst.m_loc );
	}

	bool encoding::operator == ( const encoding& other ) const
	{
		return ( m_loc == other.m_loc );
	}

	bool encoding::operator != ( const encoding& other ) const
	{
		return ( m_loc != other.m_loc );
	}

	encoding::encoding( const string_ansi& charset )
	{
		//static boost::locale::generator s_gen;
		
		//m_loc = s_gen( charset.buffer() );
		m_loc = std::locale( charset.buffer() );
	}

	encoding::encoding( const encoding& other )
		: m_loc( other.m_loc )
	{

	}

	const encoding& encoding::operator=( const encoding& other )
	{
		m_loc = other.m_loc;
		return *this;
	}

	void encoding::from_wide( const string_wide& input, string_ansi& output ) const
	{
		output = boost::locale::conv::from_utf<wchar_t>( input.buffer(), m_loc );
	}

	string_ansi encoding::from_wide( const string_wide& input ) const
	{
		return boost::locale::conv::from_utf<wchar_t>( input.buffer(), m_loc );
	}

	void encoding::to_wide( const string_ansi& input, string_wide& output ) const
	{
		output = boost::locale::conv::to_utf<wchar_t>( input.buffer(), m_loc );
	}

	string_wide encoding::to_wide( const string_ansi& input ) const
	{
		return boost::locale::conv::to_utf<wchar_t>( input.buffer(), m_loc );
	}

	const char* encoding::name() const
	{
		return m_loc.c_str();
	}
}