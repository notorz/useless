//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_IO_BINARY_WRITER_STL_SET_INCLUDED
#define USELESS_CORE_NATIVE_IO_BINARY_WRITER_STL_SET_INCLUDED

#include <set>
#include <unordered_set>

namespace useless
{
    template<typename Key, typename Compare, typename Allocator>
	struct binary_write_helper<std::set<Key, Compare, Allocator>>
	{
		template<typename Archive>
		static void write_member( Archive& bw, const std::set<Key, Compare, Allocator>& val )
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
		static void invoke( Archive& bw, const std::set<Key, Compare, Allocator>& val )
		{
			uint32_t count = static_cast< uint32_t >( val.size() );
			bw.write( &count, sizeof( uint32_t ) );
			write_member( bw, val );
		}
    };
    
    template<typename Key, typename Compare, typename Allocator>
    struct binary_write_helper<std::multiset<Key, Compare, Allocator>>
    {
		template<typename Archive>
		static void write_member( Archive& bw, const std::multiset<Key, Compare, Allocator>& val )
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
		static void invoke( Archive& bw, const std::multiset<Key, Compare, Allocator>& val )
		{
			uint32_t count = static_cast< uint32_t >( val.size() );
			bw.write( &count, sizeof( uint32_t ) );
			write_member( bw, val );
		}
    };
    
    template<typename Key, typename Hasher, typename Compare, typename Allocator>
    struct binary_write_helper<std::unordered_set<Key, Hasher, Compare, Allocator>>
    {
		template<typename Archive>
		static void write_member( Archive& bw, const std::unordered_set<Key, Hasher, Compare, Allocator>& val )
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
		static void invoke( Archive& bw, const std::unordered_set<Key, Hasher, Compare, Allocator>& val )
		{
			uint32_t count = static_cast< uint32_t >( val.size() );
			bw.write( &count, sizeof( uint32_t ) );
			write_member( bw, val );
		}
    };
}

#endif //USELESS_CORE_NATIVE_IO_BINARY_WRITER_STL_SET_INCLUDED