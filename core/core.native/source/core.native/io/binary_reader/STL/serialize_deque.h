//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_IO_BINARY_READER_STL_DEQUE_INCLUDED
#define USELESS_CORE_NATIVE_IO_BINARY_READER_STL_DEQUE_INCLUDED

#include <type_traits>
#include <deque>

namespace useless
{
    template<typename Type, typename Allocator>
	struct binary_read_helper<std::deque<Type, Allocator>>
	{
		template<typename Archive>
		static void read_member( Archive& br, std::deque<Type, Allocator>& val, uint32_t count, std::true_type )
		{
			br.read( &val[ 0 ], sizeof( Type ) * count );
		}

		template<typename Archive>
		static void read_member( Archive& br, std::deque<Type, Allocator>& val, uint32_t count, std::false_type )
		{
			for( uint32_t i = 0; i < count; ++i )
			{
				br.read( val[ i ] );
			}
		}

		template<typename Archive>
		static void read_member( Archive& br, std::deque<Type, Allocator>& val, uint32_t count )
		{
			if( !val.empty() )
			{
				typedef typename std::is_arithmetic<typename std::remove_const<Type>::type> use_optimized;
				read_member( br, val, count, use_optimized() );
			}
		}

		template<typename Archive>
		static void invoke( Archive& br, std::deque<Type, Allocator>& val )
		{
			uint32_t current_count = static_cast< uint32_t >( val.size() );
			
			uint32_t count;
			br.read( &count, sizeof( uint32_t ) );
			
			if( count > current_count )
			{
				val.resize( count );
			}

			read_member( br, val, count );
		}
    };
}

#endif //USELESS_CORE_NATIVE_IO_BINARY_READER_STL_DEQUE_INCLUDED