//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_IO_INCLUDED
#define USELESS_CORE_NATIVE_IO_INCLUDED

#include "io/stream/memory_stream.h"
#include "io/stream/fixed_stream.h"
#include "io/stream/dynamic_stream.h"
#include "io/stream/file_stream.h"
#include "io/binary_writer/binary_writer.h"
#include "io/binary_writer/STL/string.h"
#include "io/binary_writer/STL/vector.h"
#include "io/binary_writer/STL/array.h"
#include "io/binary_writer/STL/deque.h"
#include "io/binary_writer/STL/list.h"
#include "io/binary_writer/STL/pair.h"
#include "io/binary_writer/STL/set.h"
#include "io/binary_writer/STL/map.h"

namespace useless
{
	typedef basic_fixed_stream<std::allocator<char>> fixed_stream;
	typedef basic_dynamic_stream<std::allocator<char>> dynamic_stream;
	typedef basic_binary_writer<std::allocator<char>> binary_writer;
}

#endif USELESS_CORE_NATIVE_IO_INCLUDED
