//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_STREAM_MEMORYSTREAM_INCLUDED
#define USELESS_CORE_NATIVE_STREAM_MEMORYSTREAM_INCLUDED

#include "streambuf.h"
#include "memorybuf.h"
#include "fixedbuf.h"
#include "dynamicbuf.h"

namespace useless
{
	template<typename Allocator>
	class basic_memorystream
	{
	public:
		basic_memorystream()
			: m_streambuf( NULL )
		{

		}

		basic_memorystream( size_t size, bool growable = true )
		{
			create( size, growable );
		}

		basic_memorystream( void* address, size_t size )
		{
			open( address, size );
		}

		~basic_memorystream()
		{
			close();
		}

		void create( size_t size, bool growable = true )
		{
			close();

			// stream 생성에 대한 Allocator도 템플릿 인자로 받아야 하려나...
			if( growable )
			{
				m_streambuf = new basic_dynamicbuf<Allocator>( size );
			}
			else
			{
				m_streambuf = new basic_fixedbuf<Allocator>( size );
			}
		}

		void open( void* address, size_t size )
		{
			close();

			// stream 생성에 대한 Allocator도 템플릿 인자로 받아야 하려나...
			m_streambuf = new memorybuf( address, size );
		}

		void close()
		{
			delete m_streambuf;
			m_streambuf = NULL;
		}

		bool is_open() const
		{
			return ( m_streambuf != NULL );
		}

		size_t size() const
		{
			if( m_streambuf == NULL )
			{
				return 0;
			}

			return m_streambuf->size();
		}

		bool can_be_read() const
		{
			if( m_streambuf == NULL )
			{
				return false;
			}

			return m_streambuf->can_be_read();
		}

		bool can_be_write() const
		{
			if( m_streambuf == NULL )
			{
				return false;
			}

			return m_streambuf->can_be_write();
		}

		void* raw_data() const
		{
			if( m_streambuf == NULL )
			{
				return NULL;
			}

			return m_streambuf->raw_data();
		}

		int read( void* buffer, int size )
		{
			if( m_streambuf == NULL || !m_streambuf->can_be_read() )
			{
				return 0;
			}

			return m_streambuf->read( buffer, size );
		}

		int write( const void* buffer, int size )
		{
			if( m_streambuf == NULL || !m_streambuf->can_be_write() )
			{
				return 0;
			}

			return m_streambuf->write( buffer, size );
		}

	private:
		streambuf* m_streambuf;
	};
}

#endif USELESS_CORE_NATIVE_STREAM_MEMORYSTREAM_INCLUDED