//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_IO_STREAM_BASE_INCLUDED
#define USELESS_CORE_NATIVE_IO_STREAM_BASE_INCLUDED

#include <boost/cstdint.hpp>
#include "core.native/io/definitions.h"

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

	// Check windows
#if _WIN32 || _WIN64
#	if _WIN64
#		define ENV64 1
#	else
#		define ENV32 1
#	endif
#endif

	// Check GCC
#if __GNUC__
#	if __x86_64__ || __ppc64__
#		define ENV64 1
#	else
#		define ENV32 1
#	endif
#endif

#if ENV64
	typedef int64_t streamoff;
#elif ENV32
	typedef int32_t streamoff;
#endif

	class CORE_IO_DECL streambase
	{
	public:
		virtual ~streambase() = 0;

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

#endif //USELESS_CORE_NATIVE_IO_STREAM_BASE_INCLUDED