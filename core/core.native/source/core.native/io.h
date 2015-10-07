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
#include "io/binary_reader/binary_reader.h"
#include "io/binary_reader/STL/string.h"
#include "io/binary_reader/STL/vector.h"
#include "io/binary_reader/STL/array.h"
#include "io/binary_reader/STL/deque.h"
#include "io/binary_reader/STL/list.h"
#include "io/binary_reader/STL/pair.h"
#include "io/binary_reader/STL/set.h"
#include "io/binary_reader/STL/map.h"

namespace useless
{
	typedef basic_fixed_stream<std::allocator<char>> fixed_stream;
	typedef basic_dynamic_stream<std::allocator<char>> dynamic_stream;
	typedef basic_binary_writer<std::allocator<char>> binary_writer;
	typedef basic_binary_reader<std::allocator<char>> binary_reader;
}

#endif USELESS_CORE_NATIVE_IO_INCLUDED
