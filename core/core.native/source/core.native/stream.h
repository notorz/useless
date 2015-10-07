//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_STREAM_INCLUDED
#define USELESS_CORE_NATIVE_STREAM_INCLUDED

#include "stream/streambuf/memorybuf.h"
#include "stream/streambuf/fixedbuf.h"
#include "stream/streambuf/dynamicbuf.h"
#include "stream/streambuf/filebuf.h"

namespace useless
{
	typedef basic_fixedbuf<std::allocator<char>> fixedbuf;
	typedef basic_dynamicbuf<std::allocator<char>> dynamicbuf;
}

#endif USELESS_CORE_NATIVE_STREAM_INCLUDED
