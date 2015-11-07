//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_STRING_STRING_INCLUDED
#define USELESS_CORE_NATIVE_STRING_STRING_INCLUDED

#include <string>
#include <stdarg.h>
#include <boost/algorithm/string.hpp>
#include "string_helper.h"

namespace useless
{
	template<typename C, typename Allocator>
	class basic_string
	{
	public:
		typedef C char_type;
		typedef std::basic_string<char_type, std::char_traits<char_type>, Allocator> buffer_type;
		typedef typename buffer_type::const_iterator const_iterator;

	private:
		class tag_compare
		{
		private:
			const buffer_type& m_findTag;

		public:
			tag_compare( const buffer_type& findTag )
				: m_findTag( findTag )
			{
			}

			tag_compare& operator = ( const tag_compare& )
			{
				return *this;
			}

			bool operator () ( C ch ) const
			{
				return m_findTag.find( ch ) != buffer_type::npos;
			}
		};

	public:
		static size_t npos()
		{
			return buffer_type::npos;
		}

		static basic_string<char_type, Allocator> trim( const basic_string<char_type, Allocator>& other )
		{
			basic_string<char_type, Allocator> result( other );
			result.trim();
			return result;
		}

		static basic_string<char_type, Allocator> trim( const basic_string<char_type, Allocator>&& other )
		{
			basic_string<char_type, Allocator> result( other );
			result.trim();
			return result;
		}

		static basic_string<char_type, Allocator> make_upper( const basic_string<char_type, Allocator>& other )
		{
			return other.make_upper();
		}

		static basic_string<char_type, Allocator> make_lower( const basic_string<char_type, Allocator>& other )
		{
			return other.make_lower();
		}

		static int parse_int( const basic_string<char_type, Allocator>& str )
		{
			return str.get_int();
		}

		static unsigned int parse_uint( const basic_string<char_type, Allocator>& str )
		{
			return str.get_uint();
		}

		static int64_t parse_int64( const basic_string<char_type, Allocator>& str )
		{
			return str.get_int64();
		}

		static uint64_t parse_uint64( const basic_string<char_type, Allocator>& str )
		{
			return str.get_uint64();
		}

		static float parse_float( const basic_string<char_type, Allocator>& str )
		{
			return str.get_float();
		}

		static double parse_double( const basic_string<char_type, Allocator>& str )
		{
			return str.get_double();
		}

		static basic_string<char_type, Allocator> make_format( const char_type* fmt, ... )
		{
#if ( _WIN32 || _WIN64 )
			__declspec( thread ) static va_list marker;
			va_start( marker, fmt );

			__declspec( thread ) static char_type buffer[ 4096 ];
			string_helper<char_type>::format_helper( fmt, marker, buffer );

			va_end( marker );
			return basic_string<char_type, Allocator>( buffer );
#elif __GNUC__
			__thread static va_list marker;
			va_start( marker, fmt );

            static __thread char_type buffer[ 4096 ];
			string_helper<char_type>::format_helper( fmt, marker, buffer );

			va_end( marker );
			return basic_string<char_type, Allocator>( buffer );
#endif
		}

	public:
		basic_string()
			: m_buffer()
		{

		}

		basic_string( const basic_string<char_type, Allocator>& value )
			: m_buffer( value.m_buffer )
		{

		}

		basic_string( basic_string<char_type, Allocator>&& value )
			: m_buffer( std::move( value.m_buffer ) )
		{

		}

		basic_string( const char_type& ch )
			: m_buffer()
		{
			push_back( ch );
		}

		basic_string( const char_type* value )
			: m_buffer( value )
		{
		}

		basic_string( const char_type* value, size_t count )
			: m_buffer()
		{
			m_buffer.resize( count );
			::memcpy( &m_buffer[ 0 ], value, sizeof( char_type ) * count );
		}

		basic_string( const buffer_type& buffer )
			: m_buffer( buffer )
		{
		}

		basic_string( buffer_type&& buffer )
			: m_buffer( std::move( buffer ) )
		{
		}

		basic_string<char_type, Allocator>& operator = ( const basic_string<char_type, Allocator>& other )
		{
			m_buffer = other.m_buffer;

			return *this;
		}

		basic_string<char_type, Allocator>& operator = ( basic_string<char_type, Allocator>&& other )
		{
			m_buffer = std::move( other.m_buffer );

			return *this;
		}

		basic_string<char_type, Allocator>& operator += ( const basic_string<char_type, Allocator>& other )
		{
			m_buffer += other.m_buffer;

			return *this;
		}

		bool operator == ( const basic_string<char_type, Allocator>& other ) const
		{
			return m_buffer == other.m_buffer;
		}

		bool operator != ( const basic_string<char_type, Allocator>& other ) const
		{
			return m_buffer != other.m_buffer;
		}

		bool operator < ( const basic_string<char_type, Allocator>& other ) const
		{
			return m_buffer < other.m_buffer;
		}

		bool operator > ( const basic_string<char_type, Allocator>& other ) const
		{
			return m_buffer > other.m_buffer;
		}

		bool operator <= ( const basic_string<char_type, Allocator>& other ) const
		{
			return m_buffer <= other.m_buffer;
		}

		bool operator >= ( const basic_string<char_type, Allocator>& other ) const
		{
			return m_buffer >= other.m_buffer;
		}

		basic_string<char_type, Allocator> operator + ( const basic_string<char_type, Allocator>& other ) const
		{
			return basic_string( m_buffer + other.m_buffer );
		}

		char_type& operator []( size_t index )
		{
			return m_buffer[ index ];
		}

		const char_type& operator []( size_t index ) const
		{
			return m_buffer[ index ];
		}

		void reserve( size_t size )
		{
			m_buffer.reserve( size );
		}

		void resize( size_t size )
		{
			m_buffer.resize( size );
		}

		void resize( size_t size, const char_type ch )
		{
			m_buffer.resize( size, ch );
		}

		void clear()
		{
			m_buffer.clear();
		}

		void push_back( const char_type ch )
		{
			m_buffer.push_back( ch );
		}

		bool is_empty() const
		{
			return m_buffer.empty();
		}

		size_t length() const
		{
			return m_buffer.length();
		}

		const char_type* buffer() const
		{
			return m_buffer.c_str();
		}

		basic_string<char_type, Allocator>& format( const char_type* fmt, ... )
		{
			va_list marker;
			va_start( marker, fmt );

			char_type buffer[ 4096 ] = { 0, };
			string_helper<char_type>::format_helper( fmt, marker, buffer );

			va_end( marker );

			m_buffer = buffer;
			return *this;
		}

		basic_string<char_type, Allocator> sub_string( size_t index, size_t count ) const
		{
			return basic_string( m_buffer.substr( index, count ) );
		}

		basic_string<char_type, Allocator> sub_string( size_t index ) const
		{
			return basic_string( m_buffer.substr( index ) );
		}

		void erase( size_t index, size_t count )
		{
			m_buffer.erase( index, count );
		}

		void remove( const basic_string<char_type, Allocator>& term )
		{
			typename buffer_type::iterator it = std::remove_if<typename buffer_type::iterator, tag_compare>( m_buffer.begin(), m_buffer.end(), tag_compare( term.m_buffer ) );
			if( it != m_buffer.end() )
			{
				m_buffer.erase( it, m_buffer.end() );
			}
		}

		void insert( size_t pos, size_t count, char_type ch )
		{
			m_buffer.insert( pos, count, ch );
		}

		void insert( size_t pos, const basic_string<char_type, Allocator>& other )
		{
			m_buffer.insert( pos, other.m_buffer );
		}

		void insert( size_t pos, const basic_string<char_type, Allocator>& other, size_t count )
		{
			m_buffer.insert( pos, other.m_buffer, 0, count );
		}

		void insert( size_t pos, const basic_string<char_type, Allocator>& other, size_t srcPos, size_t srcCount )
		{
			m_buffer.insert( pos, other.m_buffer, srcPos, srcCount );
		}

		basic_string<char_type, Allocator>& append( const char_type* pAppend, size_t count )
		{
			m_buffer.append( pAppend, count );
			return *this;
		}

		size_t find( const char_type* value, size_t offset = 0 ) const
		{
			return m_buffer.find( value, offset );
		}

		size_t find( const basic_string<char_type, Allocator>& other, size_t offset = 0 ) const
		{
			return m_buffer.find( other.m_buffer, offset );
		}

		size_t find( const basic_string<char_type, Allocator>& other, size_t offset, size_t count ) const
		{
			return m_buffer.find( other.m_buffer.c_str(), offset, count );
		}

		size_t find( char_type char_type, size_t offset = 0 ) const
		{
			return m_buffer.find( char_type, offset );
		}

		size_t reverse_find( const char_type* value, size_t offset = -1 ) const
		{
			return m_buffer.rfind( value, offset );
		}

		size_t reverse_find( const basic_string<char_type, Allocator>& other, size_t offset = -1 ) const
		{
			return m_buffer.rfind( other.m_buffer, offset );
		}

		size_t reverse_find( const basic_string<char_type, Allocator>& other, size_t offset, size_t count ) const
		{
			return m_buffer.rfind( other.m_buffer.c_str(), offset, count );
		}

		size_t reverse_find( char_type char_type, size_t offset = -1 ) const
		{
			return m_buffer.rfind( char_type, offset );
		}

		int compare( const basic_string<char_type, Allocator>& other ) const
		{
			return m_buffer.compare( other.m_buffer );
		}

		int compare( size_t pos, size_t count, const basic_string<char_type, Allocator>& other ) const
		{
			return m_buffer.compare( pos, count, other.m_buffer );
		}

		int compare( size_t pos, size_t count, const basic_string<char_type, Allocator>& other, size_t srcCount ) const
		{
			return m_buffer.compare( pos, count, other.m_buffer, 0, srcCount );
		}

		int compare( size_t pos, size_t count, const basic_string<char_type, Allocator>& other, size_t srcPos, size_t srcCount ) const
		{
			return m_buffer.compare( pos, count, other.m_buffer, srcPos, srcCount );
		}

		void trim()
		{
			boost::trim( m_buffer );
		}

		void trim_right()
		{
			boost::trim_right( m_buffer );
		}

		void trim_left()
		{
			boost::trim_left( m_buffer );
		}

		void to_upper()
		{
			boost::to_upper( m_buffer );
		}

		void to_lower()
		{
			boost::to_lower( m_buffer );
		}

		basic_string<char_type, Allocator> make_upper() const
		{
			return boost::to_upper_copy( m_buffer );
		}

		basic_string<char_type, Allocator> make_lower() const
		{
			return boost::to_lower_copy( m_buffer );
		}

		int compare_no_case( const basic_string<char_type, Allocator>& other ) const
		{
			return string_helper<char_type>::compare_no_case( &m_buffer[ 0 ], &other[ 0 ] );
		}

		basic_string<char_type, Allocator> left( size_t count ) const
		{
			if( count >= m_buffer.size() )
			{
				return basic_string( m_buffer );
			}

			return sub_string( 0, count );
		}

		basic_string<char_type, Allocator> right( size_t count ) const
		{
			if( count >= m_buffer.size() )
			{
				return basic_string( m_buffer );
			}

			return sub_string( m_buffer.size() - count, count );
		}

		basic_string<char_type, Allocator> mid( size_t start, size_t count ) const
		{
			if( start >= m_buffer.size() || count >= m_buffer.size() )
			{
				return basic_string( m_buffer );
			}

			return sub_string( start, count );
		}

		void replace_first( const basic_string<char_type, Allocator>& findString, const basic_string<char_type, Allocator>& replaceString )
		{
			boost::algorithm::replace_first( m_buffer, findString.m_buffer, replaceString.m_buffer );
		}

		void replace_last( const basic_string<char_type, Allocator>& findString, const basic_string<char_type, Allocator>& replaceString )
		{
			boost::algorithm::replace_last( m_buffer, findString.m_buffer, replaceString.m_buffer );
		}

		void replace_all( const basic_string<char_type, Allocator>& findString, const basic_string<char_type, Allocator>& replaceString )
		{
			boost::algorithm::replace_all( m_buffer, findString.m_buffer, replaceString.m_buffer );
		}

		int get_int() const
		{
			return string_helper<char_type>::parse_int( m_buffer.c_str() );
		}

		unsigned int get_uint() const
		{
			return string_helper<char_type>::parse_uint( m_buffer.c_str() );
		}

		int64_t get_int64() const
		{
			return string_helper<char_type>::parse_int64( m_buffer.c_str() );
		}

		uint64_t get_uint64() const
		{
			return string_helper<char_type>::parse_uint64( m_buffer.c_str() );
		}

		float get_float() const
		{
			return string_helper<char_type>::parse_float( m_buffer.c_str() );
		}

		double get_double() const
		{
			return string_helper<char_type>::parse_double( m_buffer.c_str() );
		}

		bool get_bool() const
		{
			return string_helper<char_type>::parse_bool( m_buffer.c_str() );
		}

		bool start_with( const basic_string<char_type, Allocator>& findstr ) const
		{
			const size_t index = findstr.length();
			return ( length() >= index && left( index ) == findstr );
		}

		bool end_with( const basic_string<char_type, Allocator>& findstr ) const
		{
			const size_t index = findstr.length();
			return ( index >= 0 && length() >= index && right( index ) == findstr );
		}

		const_iterator begin() const
		{
			return m_buffer.begin();
		}

		const_iterator end() const
		{
			return m_buffer.end();
		}

		// serialize
		template<typename Archive>
		void serialize( Archive& ar, const unsigned int )
		{
			ar & m_buffer;
		}

	private:
		buffer_type m_buffer;
	};
}

#endif //USELESS_CORE_NATIVE_STRING_STRING_INCLUDED