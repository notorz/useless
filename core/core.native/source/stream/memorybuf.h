//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_STREAM_MEMORYBUF_INCLUDED
#define USELESS_CORE_NATIVE_STREAM_MEMORYBUF_INCLUDED

#include "streambuf.h"

namespace useless
{
	class memorybuf : public streambuf
	{
	public:
		memorybuf( void* address, size_t size )
			: m_buffer( static_cast<char*>( address ) )
			, m_size( size )
		{
			setg( m_buffer, m_buffer, m_buffer + size );
			setp( m_buffer, m_buffer + size );
		}

		virtual size_t size() const
		{
			return m_size;
		}

		virtual bool can_be_read() const
		{
			return ( egptr() > gptr() );
		}

		virtual bool can_be_write() const
		{
			return ( _Pnavail() > 0 );
		}

		virtual const void* raw_data() const
		{
			return m_buffer;
		}

		virtual int read( void* buffer, int size )
		{
			if( !can_be_read() )
			{
				return 0;
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

	private:
		char* m_buffer;
		size_t m_size;
	};
}

#endif USELESS_CORE_NATIVE_STREAM_MEMORYBUF_INCLUDED