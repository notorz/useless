//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_IO_BINARY_READER_STL_LIST_INCLUDED
#define USELESS_CORE_NATIVE_IO_BINARY_READER_STL_LIST_INCLUDED

#include <list>
#include <forward_list>

namespace useless
{
    template<typename Type, typename Allocator>
	struct binary_read_helper<std::list<Type, Allocator>>
	{
		template<typename Archive>
		static void read_member( Archive& br, std::list<Type, Allocator>& val, uint32_t count )
		{
			for( uint32_t i = 0; i < count; ++i )
			{
				Type temp;
				br.read( temp );
				val.push_back( temp );
			}
		}

		template<typename Archive>
		static void invoke( Archive& br, std::list<Type, Allocator>& val )
		{
			uint32_t count;
			br.read( &count, sizeof( uint32_t ) );
			read_member( br, val, count );
		}
    };

    template<typename Type, typename Allocator>
    struct binary_read_helper<std::forward_list<Type, Allocator>>
    {
		template<typename Archive>
		static void read_member( Archive& br, std::forward_list<Type, Allocator>& val, uint32_t count )
		{
			for( uint32_t i = 0; i < count; ++i )
			{
				Type temp;
				br.read( temp );
				val.push_back( temp );
			}
		}

		template<typename Archive>
		static void invoke( Archive& br, std::forward_list<Type, Allocator>& val )
		{
			uint32_t count;
			br.read( &count, sizeof( uint32_t ) );
			read_member( br, val, count );
		}
    };
}

#endif //USELESS_CORE_NATIVE_IO_BINARY_READER_STL_LIST_INCLUDED