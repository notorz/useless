//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_STREAM_MEMORYBUF_INCLUDED
#define USELESS_CORE_NATIVE_STREAM_MEMORYBUF_INCLUDED

#include "streambuf.h"
#include "../useless_api.h"

namespace useless
{
	class Core_API memorybuf : public streambuf
	{
	public:
		memorybuf( void* address, size_t size );

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

#endif USELESS_CORE_NATIVE_STREAM_MEMORYBUF_INCLUDED