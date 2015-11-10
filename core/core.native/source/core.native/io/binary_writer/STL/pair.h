//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_IO_BINARY_WRITER_STL_PAIR_INCLUDED
#define USELESS_CORE_NATIVE_IO_BINARY_WRITER_STL_PAIR_INCLUDED

#include <utility>

namespace useless
{
	namespace binary_write_helper
	{
		template<typename Archive, typename T1, typename T2>
		void invoke( Archive& bw, const std::pair<T1, T2>& val )
		{
			bw.write( val.first );
			bw.write( val.second );
		}
	}
}

#endif //USELESS_CORE_NATIVE_IO_BINARY_WRITER_STL_PAIR_INCLUDED