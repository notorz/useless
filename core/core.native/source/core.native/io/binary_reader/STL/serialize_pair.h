//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_IO_BINARY_READER_STL_PAIR_INCLUDED
#define USELESS_CORE_NATIVE_IO_BINARY_READER_STL_PAIR_INCLUDED

#include <utility>

namespace useless
{
    template<typename T1, typename T2>
	struct binary_read_helper<std::pair<T1, T2>>
	{
		template<typename Archive>
		static void Read( Archive& br, std::pair<T1, T2>& val )
		{
			br.read( val.first );
			br.read( val.second );
		}
    };
}

#endif //USELESS_CORE_NATIVE_IO_BINARY_READER_STL_PAIR_INCLUDED