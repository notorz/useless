//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_IO_BINARY_WRITER_STL_LIST_INCLUDED
#define USELESS_CORE_NATIVE_IO_BINARY_WRITER_STL_LIST_INCLUDED

#include <list>
#include <forward_list>

namespace useless
{
    template<typename Type, typename Allocator>
	struct binary_write_helper<std::list<Type, Allocator>>
	{
		template<typename Archive>
		static void write_member( Archive& bw, const std::list<Type, Allocator>& val )
		{
			if( !val.empty() )
			{
				auto endit = val.end();
				for( auto it = val.begin(); it != endit; ++it )
				{
					bw.write( *it );
				}
			}
		}

		template<typename Archive>
		static void invoke( Archive& bw, const std::list<Type, Allocator>& val )
		{
			uint32_t count = static_cast< uint32_t >( val.size() );
			bw.write( &count, sizeof( uint32_t ) );
			write_member( bw, val );
		}
    };
    
    template<typename Type, typename Allocator>
    struct binary_write_helper<std::forward_list<Type, Allocator>>
    {
		template<typename Archive>
		static void write_member( Archive& bw, const std::forward_list<Type, Allocator>& val )
		{
			if( !val.empty() )
			{
				auto endit = val.end();
				for( auto it = val.begin(); it != endit; ++it )
				{
					bw.write( *it );
				}
			}
		}

		template<typename Archive>
		static void invoke( Archive& bw, const std::forward_list<Type, Allocator>& val )
		{
			uint32_t count = 0;
			if( !val.empty() )
			{
				auto endit = val.end();
				for( auto it = val.begin(); it != endit; ++it )
				{
					++count;
				}
			}

			bw.write( &count, sizeof( uint32_t ) );
			write_member( bw, val );
		}
    };
}

#endif //USELESS_CORE_NATIVE_IO_BINARY_WRITER_STL_LIST_INCLUDED