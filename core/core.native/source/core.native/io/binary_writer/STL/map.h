//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_IO_BINARY_WRITER_STL_MAP_INCLUDED
#define USELESS_CORE_NATIVE_IO_BINARY_WRITER_STL_MAP_INCLUDED

#include <map>
#include <unordered_map>

namespace useless
{
	namespace binary_write_helper
	{
		template<typename Archive, typename Key, typename Type, typename Compare, typename Allocator>
		void write_member( Archive& bw, const std::map<Key, Type, Compare, Allocator>& val )
		{
			if( !val.empty() )
			{
				auto endit = val.end();
				for( auto it = val.begin(); it != endit; ++it )
				{
					bw.write( it->first );
					bw.write( it->second );
				}
			}
		}

		template<typename Archive, typename Key, typename Type, typename Compare, typename Allocator>
		void invoke( Archive& bw, const std::map<Key, Type, Compare, Allocator>& val )
		{
			unsigned long count = static_cast< unsigned long >( val.size() );
			bw.write( &count, sizeof( unsigned long ) );
			write_member( bw, val );
		}

		template<typename Archive, typename Key, typename Type, typename Compare, typename Allocator>
		void write_member( Archive& bw, const std::multimap<Key, Type, Compare, Allocator>& val )
		{
			if( !val.empty() )
			{
				auto endit = val.end();
				for( auto it = val.begin(); it != endit; ++it )
				{
					bw.write( it->first );
					bw.write( it->second );
				}
			}
		}

		template<typename Archive, typename Key, typename Type, typename Compare, typename Allocator>
		void invoke( Archive& bw, const std::multimap<Key, Type, Compare, Allocator>& val )
		{
			unsigned long count = static_cast< unsigned long >( val.size() );
			bw.write( &count, sizeof( unsigned long ) );
			write_member( bw, val );
		}

		template<typename Archive, typename Key, typename Type, typename Hasher, typename Compare, typename Allocator>
		void write_member( Archive& bw, const std::unordered_map<Key, Type, Hasher, Compare, Allocator>& val )
		{
			if( !val.empty() )
			{
				auto endit = val.end();
				for( auto it = val.begin(); it != endit; ++it )
				{
					bw.write( it->first );
					bw.write( it->second );
				}
			}
		}

		template<typename Archive, typename Key, typename Type, typename Hasher, typename Compare, typename Allocator>
		void invoke( Archive& bw, const std::unordered_map<Key, Type, Hasher, Compare, Allocator>& val )
		{
			unsigned long count = static_cast< unsigned long >( val.size() );
			bw.write( &count, sizeof( unsigned long ) );
			write_member( bw, val );
		}
	}
}

#endif //USELESS_CORE_NATIVE_IO_BINARY_WRITER_STL_MAP_INCLUDED