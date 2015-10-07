//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_IO_BINARY_READER_STL_STRING_INCLUDED
#define USELESS_CORE_NATIVE_IO_BINARY_READER_STL_STRING_INCLUDED

#include <string>

namespace useless
{
	namespace binary_read_helper
	{
		template<typename Archive, typename C, typename Allocator>
		void read_member( Archive& br, std::basic_string<C, Allocator>& val, unsigned long count )
		{
			if( !val.empty() )
			{
				br.read( &val[ 0 ], sizeof( C ) * count );
			}
		}

		template<typename Archive, typename C, typename Allocator>
		void invoke( Archive& br, std::basic_string<C, Allocator>& val )
		{
			unsigned long current_count = static_cast< unsigned long >( val.size() );

			unsigned long count;
			br.read( &count, sizeof( unsigned long ) );

			if( count > current_count )
			{
				val.resize( count );
			}

			read_member( br, val, count );
		}
	}
}

#endif USELESS_CORE_NATIVE_IO_BINARY_READER_STL_STRING_INCLUDED