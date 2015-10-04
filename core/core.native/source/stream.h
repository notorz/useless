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
#include "stream/filebuf.h"

namespace useless
{
	typedef basic_fixedbuf<std::allocator<char>> fixedbuf;
	typedef basic_dynamicbuf<std::allocator<char>> dynamicbuf;
}

#endif USELESS_CORE_NATIVE_STREAM_INCLUDED
