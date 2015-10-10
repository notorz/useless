//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_IO_MEMORY_STREAM_INCLUDED
#define USELESS_CORE_NATIVE_IO_MEMORY_STREAM_INCLUDED

#include "core.native/io/definitions.h"
#include "streambase.h"

namespace useless
{
	class CORE_IO_DECL memory_stream : public streambase
	{
	public:
		memory_stream( void* address, size_t size );

		virtual size_t size() const;
		virtual bool can_be_read() const;
		virtual bool can_be_write() const;
		virtual const void* raw_data() const;
		virtual size_t read( void* buffer, size_t count );
		virtual size_t write( const void* buffer, size_t count );
		virtual streamoff setpos( seekdir::type way, streamoff off );
		virtual streamoff getpos() const;

	private:
		char* m_base;
		char* m_next;
		char* m_end;
		size_t m_size;
	};
}

#endif USELESS_CORE_NATIVE_IO_MEMORY_STREAM_INCLUDED