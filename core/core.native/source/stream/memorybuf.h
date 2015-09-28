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

	protected:
		virtual pos_type seekoff( off_type off,
			std::ios_base::seekdir way,
			std::ios_base::openmode which =
			( std::ios_base::openmode )( std::ios_base::in | std::ios_base::out ) )
		{
			if( which & std::ios_base::in )
			{
				if( way == std::ios_base::end )
				{
					off += static_cast< off_type >( egptr() - eback() );
				}
				else if( way == std::ios_base::cur && which & std::ios_base::out )
				{
					off += static_cast< off_type >( gptr() - eback() );
				}
				else if( way != std::ios_base::beg )
				{
					off = std::_BADOFF;
				}

				if( off >= 0 && egptr() - eback() >= off )
				{
					gbump( static_cast< int >( eback() - gptr() + off ) );
					if( which & std::ios_base::out )
					{
						setp( pbase(), gptr(), epptr() );
					}
				}
				else
				{
					off = std::_BADOFF;
				}
			}
			else if( which & std::ios_base::out )
			{
				if( way == std::ios_base::end )
				{
					off += static_cast< off_type >( epptr() - pbase() );
				}
				else if( way == std::ios_base::cur )
				{
					off += static_cast< off_type >( pptr() - pbase() );
				}
				else if( way != std::ios_base::beg )
				{
					off = std::_BADOFF;
				}

				if( off >= 0 && epptr() - pbase() >= off )
				{
					pbump( static_cast< int >( pbase() - pptr() + off ) );
				}
				else
				{
					off = std::_BADOFF;
				}
			}
			else if( off != 0 )
			{
				off = std::_BADOFF;
			}

			return pos_type( off );
		}

		virtual pos_type seekpos( pos_type pos,
			std::ios_base::openmode mode =
			( std::ios_base::openmode )( std::ios_base::in | std::ios_base::out ) )
		{
			off_type off = static_cast< off_type >( pos );
			if( off != std::_BADOFF )
			{
				return seekoff( off, std::ios_base::beg, mode );
			}

			return pos_type( off );
		}

	private:
		char* m_buffer;
		size_t m_size;
	};
}

#endif USELESS_CORE_NATIVE_STREAM_MEMORYBUF_INCLUDED