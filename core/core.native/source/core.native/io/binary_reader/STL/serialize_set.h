//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_IO_BINARY_READER_STL_SET_INCLUDED
#define USELESS_CORE_NATIVE_IO_BINARY_READER_STL_SET_INCLUDED

#include <set>
#include <unordered_set>

namespace useless
{
    template<typename Key, typename Compare, typename Allocator>
	struct binary_read_helper<std::set<Key, Compare, Allocator>>
	{
		template<typename Archive>
		static void read_member( Archive& br, std::set<Key, Compare, Allocator>& val, uint32_t count )
		{
			for( uint32_t i = 0; i < count; ++i )
			{
				Key key;
				br.read( key );
				val.insert( key );
			}
		}

		template<typename Archive>
		static void invoke( Archive& br, std::set<Key, Compare, Allocator>& val )
		{
			uint32_t count;
			br.read( &count, sizeof( uint32_t ) );
			read_member( br, val, count );
		}
    };

    template<typename Key, typename Compare, typename Allocator>
    struct binary_read_helper<std::multiset<Key, Compare, Allocator>>
    {
		template<typename Archive>
		static void read_member( Archive& br, std::multiset<Key, Compare, Allocator>& val, uint32_t count )
		{
			for( uint32_t i = 0; i < count; ++i )
			{
				Key key;
				br.read( key );
				val.insert( key );
			}
		}

		template<typename Archive>
		static void invoke( Archive& br, std::multiset<Key, Compare, Allocator>& val )
		{
			uint32_t count;
			br.read( &count, sizeof( uint32_t ) );
			read_member( br, val, count );
		}
    };

    template<typename Key, typename Hasher, typename Compare, typename Allocator>
    struct binary_read_helper<std::unordered_set<Key, Hasher, Compare, Allocator>>
    {
		template<typename Archive>
		static void read_member( Archive& br, std::unordered_set<Key, Hasher, Compare, Allocator>& val, uint32_t count )
		{
			for( uint32_t i = 0; i < count; ++i )
			{
				Key key;
				br.read( key );
				val.insert( key );
			}
		}

		template<typename Archive>
		static void invoke( Archive& br, std::unordered_set<Key, Hasher, Compare, Allocator>& val )
		{
			uint32_t count;
			br.read( &count, sizeof( uint32_t ) );
			read_member( br, val, count );
		}
    };
}

#endif //USELESS_CORE_NATIVE_IO_BINARY_READER_STL_SET_INCLUDED