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
			char* base = &m_buffer[ 0 ];
			setg( base, base, base );
			setp( base, base + size );
			m_seekhigh = base;
		}

		virtual size_t size() const
		{
			return m_buffer.size();
		}

		virtual bool can_be_read() const
		{
			return ( egptr() > gptr() ) || ( ( m_seekhigh < pptr() ? pptr() : m_seekhigh ) > gptr() );
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

			if( egptr() - gptr() < size )
			{
				if( m_seekhigh < pptr() )
				{
					m_seekhigh = pptr();
				}

				if( gptr() < m_seekhigh )
				{
					setg( &m_buffer[ 0 ], gptr(), m_seekhigh );
				}
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
			if( m_seekhigh < pptr() )
			{
				m_seekhigh = pptr();
			}

			if( gptr() < m_seekhigh )
			{
				setg( &m_buffer[ 0 ], gptr(), m_seekhigh );
				return traits_type::to_int_type( *gptr() );
			}

			return traits_type::eof();
		}

		virtual pos_type seekoff( off_type off,
			std::ios_base::seekdir way,
			std::ios_base::openmode which =
			( std::ios_base::openmode )( std::ios_base::in | std::ios_base::out ) )
		{
			if( m_seekhigh < pptr() )
			{
				m_seekhigh = pptr();
			}

			if( which & std::ios_base::in )
			{
				if( way == std::ios_base::end )
				{
					off += static_cast< off_type >( m_seekhigh - eback() );
				}
				else if( way == std::ios_base::cur && which & std::ios_base::out )
				{
					off += static_cast< off_type >( gptr() - eback() );
				}
				else if( way != std::ios_base::beg )
				{
					off = std::_BADOFF;
				}

				if( off >= 0 && m_seekhigh - eback() >= off )
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
					off += static_cast< off_type >( m_seekhigh - pbase() );
				}
				else if( way == std::ios_base::cur )
				{
					off += static_cast< off_type >( pptr() - pbase() );
				}
				else if( way != std::ios_base::beg )
				{
					off = std::_BADOFF;
				}

				if( off >= 0 && m_seekhigh - pbase() >= off )
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
		std::vector<char, Allocator> m_buffer;
		char* m_seekhigh;
	};
}

#endif USELESS_CORE_NATIVE_STREAM_FIXEDBUF_INCLUDED