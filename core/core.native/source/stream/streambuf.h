//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_STREAM_STREAMBUF_INCLUDED
#define USELESS_CORE_NATIVE_STREAM_STREAMBUF_INCLUDED

#include <streambuf>

namespace useless
{
	class streambuf : public std::streambuf
	{
	public:
		virtual size_t size() const = 0;
		virtual bool can_be_read() const = 0;
		virtual bool can_be_write() const = 0;
		virtual const void* raw_data() const = 0;
		virtual int read( void* buffer, int size ) = 0;
		virtual int write( const void* buffer, int size ) = 0;
	};
}

#endif USELESS_CORE_NATIVE_STREAM_STREAMBUF_INCLUDED