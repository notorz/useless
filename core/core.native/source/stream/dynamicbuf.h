//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_STREAM_DYNAMICBUF_INCLUDED
#define USELESS_CORE_NATIVE_STREAM_DYNAMICBUF_INCLUDED

#include <vector>
#include "streambuf.h"

namespace useless
{
	template<typename Allocator>
	class basic_dynamicbuf : public streambuf
	{
	public:
		basic_dynamicbuf( size_t size )
			: m_buffer( size )
		{
			setg( &m_buffer[ 0 ], &m_buffer[ 0 ], &m_buffer[ 0 ] );
			setp( &m_buffer[ 0 ], &m_buffer[ 0 ] + size );
		}

		virtual size_t size() const
		{
			return m_buffer.size();
		}

		virtual bool can_be_read() const
		{
			return ( egptr() > gptr() ) || ( pptr() > gptr() );
		}

		virtual bool can_be_write() const
		{
			return true;
		}

		virtual const void* raw_data() const
		{
			return &m_buffer[ 0 ];
		}

		virtual int read( void* buffer, int size )
		{
			if( !can_be_read() )
			{
				return 0;
			}

			if( gptr() < pptr() )
			{
				setg( &m_buffer[ 0 ], gptr(), pptr() );
			}

			int read = ( ( gptr() + size ) > egptr() ) ? static_cast<int>( egptr() - gptr() ) : size;

			::memcpy_s( buffer, read, gptr(), read );
			gbump( read );

			return read;
		}

		virtual int write( const void* buffer, int size )
		{
			if( !can_be_write() )
			{
				return 0;
			}

			if( ( pptr() + size ) > epptr() )
			{
				size_t gnext_pos = gptr() - &m_buffer[ 0 ];
				size_t pnext_pos = pptr() - &m_buffer[ 0 ];

				m_buffer.resize( ( pptr() + size ) - epptr() + m_buffer.size() );
				m_buffer.resize( m_buffer.capacity() );

				setg( &m_buffer[ 0 ], &m_buffer[ 0 ] + gnext_pos, &m_buffer[ 0 ] + pnext_pos );
				setp( &m_buffer[ 0 ], &m_buffer[ 0 ] + pnext_pos, &m_buffer[ 0 ] + m_buffer.size() );
			}
			
			::memcpy_s( pptr(), size, buffer, size );
			pbump( size );

			return size;
		}

		void reserve( size_t count )
		{
			m_buffer.reserve( count );
		}

	protected:
		virtual int_type overflow( int_type meta = traits_type::eof() )
		{
			if( traits_type::eq_int_type( traits_type::eof(), meta ) )
			{
				return traits_type::not_eof( meta );
			}

			if( pptr() != epptr() )
			{
				*pptr() = traits_type::to_char_type( meta );
				pbump( 1 );
			}
			else
			{
				size_t gnext_pos = gptr() - &m_buffer[ 0 ];
				size_t pnext_pos = pptr() - &m_buffer[ 0 ];

				m_buffer.push_back( traits_type::to_char_type( meta ) );
				++pnext_pos;

				m_buffer.resize( m_buffer.capacity() );

				setg( &m_buffer[ 0 ], &m_buffer[ 0 ] + gnext_pos, &m_buffer[ 0 ] + pnext_pos );
				setp( &m_buffer[ 0 ], &m_buffer[ 0 ] + pnext_pos, &m_buffer[ 0 ] + m_buffer.size() );
			}

			return meta;
		}

		virtual int_type underflow()
		{
			if( gptr() < pptr() )
			{
				setg( &m_buffer[ 0 ], gptr(), pptr() );
				return traits_type::to_int_type( *gptr() );
			}

			return traits_type::eof();
		}

	private:
		std::vector<char, Allocator> m_buffer;
	};
}

#endif USELESS_CORE_NATIVE_STREAM_DYNAMICBUF_INCLUDED