//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_IO_DYNAMIC_STREAM_INCLUDED
#define USELESS_CORE_NATIVE_IO_DYNAMIC_STREAM_INCLUDED

#include <vector>
#include "streambase.h"

namespace useless
{
	template<typename Allocator>
	class basic_dynamic_stream : public streambase
	{
	public:
		basic_dynamic_stream( size_t size )
			: m_buffer( size )
		{
			m_base = m_next = &m_buffer[ 0 ];
			m_end = m_base + size;
			m_seekhigh = m_base;
		}

		virtual size_t size() const
		{
			return m_buffer.size();
		}

		virtual bool can_be_read() const
		{
			return ( m_seekhigh > m_next );
		}

		virtual bool can_be_write() const
		{
			return true;
		}

		virtual const void* raw_data() const
		{
			return &m_buffer[ 0 ];
		}

		virtual size_t read( void* buffer, size_t count )
		{
			if( !can_be_read() )
			{
				return 0;
			}

			size_t read = ( ( m_next + count ) > m_seekhigh ) ? ( m_seekhigh - m_next ) : count;

			::memcpy_s( buffer, read, m_next, read );
			m_next += read;

			return read;
		}

		virtual size_t write( const void* buffer, size_t count )
		{
			if( !can_be_write() )
			{
				return 0;
			}

			if( ( m_next + count ) > m_end )
			{
				size_t nextpos = m_next - m_base;
				size_t seekhighoff = m_seekhigh - m_base;
				
				m_buffer.resize( ( ( m_next + count ) - m_end ) + m_buffer.size() );
				m_buffer.resize( m_buffer.capacity() );

				m_base = &m_buffer[ 0 ];
				m_next = m_base + nextpos;
				m_end = m_base + m_buffer.size();
				m_seekhigh = m_base + seekhighoff;
			}
			
			::memcpy_s( m_next, count, buffer, count );
			m_next += count;

			if( m_next > m_seekhigh )
			{
				m_seekhigh = m_next;
			}

			return count;
		}

		virtual streamoff setpos( seekdir::type way, streamoff off )
		{
			if( way == seekdir::end )
			{
				off += static_cast< streamoff >( m_seekhigh - m_base );
			}
			else if( way == seekdir::cur )
			{
				off += static_cast< streamoff >( m_next - m_base );
			}

			if( off >= 0 && ( m_seekhigh - m_base ) >= off )
			{
				m_next = m_base + off;
			}
			else
			{
				off = -1;
			}

			return off;
		}

		virtual streamoff getpos() const
		{
			return static_cast< streamoff >( m_next - m_base );
		}

		void reserve( size_t count )
		{
			m_buffer.reserve( count );
		}

	private:
		std::vector<char, Allocator> m_buffer;
		char* m_base;
		char* m_next;
		char* m_end;
		char* m_seekhigh;
	};
}

#endif //USELESS_CORE_NATIVE_IO_DYNAMIC_STREAM_INCLUDED