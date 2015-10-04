//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_STREAM_STREAMBUF_INCLUDED
#define USELESS_CORE_NATIVE_STREAM_STREAMBUF_INCLUDED

namespace useless
{
	namespace seekdir
	{
		enum type
		{
			beg,
			cur,
			end
		};
	}

#ifdef _WIN64
	typedef __int64 streamoff;
#elif _WIN32
	typedef int streamoff;
#endif

	class streambuf
	{
	public:
		virtual size_t size() const = 0;
		virtual bool can_be_read() const = 0;
		virtual bool can_be_write() const = 0;
		virtual const void* raw_data() const = 0;
		virtual size_t read( void* buffer, size_t count ) = 0;
		virtual size_t write( const void* buffer, size_t count ) = 0;
		virtual streamoff setpos( seekdir::type way, streamoff off ) = 0;
		virtual streamoff getpos() const = 0;
	};
}

#endif USELESS_CORE_NATIVE_STREAM_STREAMBUF_INCLUDED