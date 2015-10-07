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
	namespace binary_write_helper
	{
		template<typename Archive, typename Key, typename Compare, typename Allocator>
		void write_member( Archive& bw, const std::set<Key, Compare, Allocator>& val )
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

		template<typename Archive, typename Key, typename Compare, typename Allocator>
		void invoke( Archive& bw, const std::set<Key, Compare, Allocator>& val )
		{
			unsigned long count = static_cast< unsigned long >( val.size() );
			bw.write( &count, sizeof( unsigned long ) );
			write_member( bw, val );
		}

		template<typename Archive, typename Key, typename Compare, typename Allocator>
		void write_member( Archive& bw, const std::multiset<Key, Compare, Allocator>& val )
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

		template<typename Archive, typename Key, typename Compare, typename Allocator>
		void invoke( Archive& bw, const std::multiset<Key, Compare, Allocator>& val )
		{
			unsigned long count = static_cast< unsigned long >( val.size() );
			bw.write( &count, sizeof( unsigned long ) );
			write_member( bw, val );
		}

		template<typename Archive, typename Key, typename Hasher, typename Compare, typename Allocator>
		void write_member( Archive& bw, const std::unordered_set<Key, Hasher, Compare, Allocator>& val )
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

		template<typename Archive, typename Key, typename Hasher, typename Compare, typename Allocator>
		void invoke( Archive& bw, const std::unordered_set<Key, Hasher, Compare, Allocator>& val )
		{
			unsigned long count = static_cast< unsigned long >( val.size() );
			bw.write( &count, sizeof( unsigned long ) );
			write_member( bw, val );
		}
	}
}

#endif USELESS_CORE_NATIVE_IO_BINARY_WRITER_STL_SET_INCLUDED