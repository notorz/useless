//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_STREAM_INCLUDED
#define USELESS_CORE_NATIVE_STREAM_INCLUDED

#include "stream/memorybuf.h"
#include "stream/fixedbuf.h"
#include "stream/dynamicbuf.h"
#include "stream/memorystream.h"

namespace useless
{
	typedef basic_fixedbuf<std::allocator<char>> fixedbuf;
	typedef basic_dynamicbuf<std::allocator<char>> dynamicbuf;
	using std::filebuf;
	typedef basic_memorystream<std::allocator<char>> memorystream;
}

#endif USELESS_CORE_NATIVE_STREAM_INCLUDED
