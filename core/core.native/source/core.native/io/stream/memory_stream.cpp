//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#define USELESS_IO_SOURCE
#include <memory.h>
#include "memory_stream.h"

namespace useless
{
	memory_stream::memory_stream( void* address, size_t size )
		: m_base( static_cast<char*>( address ) )
		, m_size( size )
	{
		m_next = m_base;
		m_end = m_base + size;
	}

	size_t memory_stream::size() const
	{
		return m_size;
	}

	bool memory_stream::can_be_read() const
	{
		return true;
	}

	bool memory_stream::can_be_write() const
	{
		return ( m_end > m_next );
	}

	const void* memory_stream::raw_data() const
	{
		return m_base;
	}

	size_t memory_stream::read( void* buffer, size_t count )
	{
		if( !can_be_read() )
		{
			return 0;
		}

		size_t read = ( ( m_next + count ) > m_end ) ? ( m_end - m_next ) : count;

		::memcpy_s( buffer, read, m_next, read );
		m_next += read;

		return read;
	}

	size_t memory_stream::write( const void* buffer, size_t count )
	{
		if( !can_be_write() )
		{
			return 0;
		}

		size_t write = ( ( m_next + count ) > m_end ) ? ( m_end - m_next ) : count;

		::memcpy_s( m_next, write, buffer, write );
		m_next += write;

		return write;
	}

	streamoff memory_stream::setpos( seekdir::type way, streamoff off )
	{
		if( way == seekdir::end )
		{
			off += static_cast< streamoff >( m_end - m_base );
		}
		else if( way == seekdir::cur )
		{
			off += static_cast< streamoff >( m_next - m_base );
		}

		if( off >= 0 && ( m_end - m_base ) >= off )
		{
			m_next = m_base + off;
		}
		else
		{
			off = -1;
		}

		return off;
	}

	streamoff memory_stream::getpos() const
	{
		return static_cast< streamoff >( m_next - m_base );
	}
}