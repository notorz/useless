//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_IO_BINARY_WRITER_STL_STRING_INCLUDED
#define USELESS_CORE_NATIVE_IO_BINARY_WRITER_STL_STRING_INCLUDED

#include <string>

namespace useless
{
	namespace binary_write_helper
	{
		template<typename Archive, typename C, typename Allocator>
		void write_member( Archive& bw, const std::basic_string<C, Allocator>& val, unsigned long count )
		{
			if( !val.empty() )
			{
				bw.write( &val[ 0 ], sizeof( C ) * count );
			}
		}

		template<typename Archive, typename C, typename Allocator>
		void invoke( Archive& bw, const std::basic_string<C, Allocator>& val )
		{
			unsigned long count = static_cast< unsigned long >( val.size() );
			bw.write( &count, sizeof( unsigned long ) );
			write_member( bw, val, count );
		}
	}
}

#endif //USELESS_CORE_NATIVE_IO_BINARY_WRITER_STL_STRING_INCLUDED