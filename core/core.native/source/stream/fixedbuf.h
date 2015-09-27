//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_STREAM_FIXEDBUF_INCLUDED
#define USELESS_CORE_NATIVE_STREAM_FIXEDBUF_INCLUDED

#include <vector>
#include "streambuf.h"

namespace useless
{
	template<typename Allocator>
	class basic_fixedbuf : public streambuf
	{
	public:
		basic_fixedbuf( size_t size )
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
			return ( _Pnavail() > 0 );
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

			int write = ( ( pptr() + size ) > epptr() ) ? static_cast< int >( epptr() - pptr() ) : size;

			::memcpy_s( pptr(), write, buffer, write );
			pbump( write );

			return write;
		}

	protected:
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

#endif USELESS_CORE_NATIVE_STREAM_FIXEDBUF_INCLUDED