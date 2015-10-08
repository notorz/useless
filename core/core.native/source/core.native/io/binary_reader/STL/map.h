//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_IO_BINARY_READER_STL_MAP_INCLUDED
#define USELESS_CORE_NATIVE_IO_BINARY_READER_STL_MAP_INCLUDED

#include <map>
#include <unordered_map>

namespace useless
{
	namespace binary_read_helper
	{
		template<typename Archive, typename Key, typename Type, typename Compare, typename Allocator>
		void read_member( Archive& br, std::map<Key, Type, Compare, Allocator>& val, unsigned long count )
		{
			for( unsigned long i = 0; i < count; ++i )
			{
				Key key;
				br.read( key );

				Type value;
				br.read( value );

				val[ key ] = value;
			}
		}

		template<typename Archive, typename Key, typename Type, typename Compare, typename Allocator>
		void invoke( Archive& br, std::map<Key, Type, Compare, Allocator>& val )
		{
			unsigned long count;
			br.read( &count, sizeof( unsigned long ) );
			read_member( br, val, count );
		}

		template<typename Archive, typename Key, typename Type, typename Compare, typename Allocator>
		void read_member( Archive& br, std::multimap<Key, Type, Compare, Allocator>& val, unsigned long count )
		{
			for( unsigned long i = 0; i < count; ++i )
			{
				Key key;
				br.read( key );

				Type value;
				br.Read( value );

				val.insert( std::make_pair( key, value ) );
			}
		}

		template<typename Archive, typename Key, typename Type, typename Compare, typename Allocator>
		void invoke( Archive& br, std::multimap<Key, Type, Compare, Allocator>& val )
		{
			unsigned long count;
			br.read( &count, sizeof( unsigned long ) );
			read_member( br, val, count );
		}

		template<typename Archive, typename Key, typename Type, typename Hasher, typename Compare, typename Allocator>
		void read_member( Archive& br, std::unordered_map<Key, Type, Hasher, Compare, Allocator>& val, unsigned long count )
		{
			for( unsigned long i = 0; i < count; ++i )
			{
				Key key;
				br.read( key );

				Type value;
				br.Read( value );

				val.insert( std::make_pair( key, value ) );
			}
		}

		template<typename Archive, typename Key, typename Type, typename Hasher, typename Compare, typename Allocator>
		void invoke( Archive& br, std::unordered_map<Key, Type, Hasher, Compare, Allocator>& val )
		{
			unsigned long count;
			br.read( &count, sizeof( unsigned long ) );
			read_member( br, val, count );
		}
	}
}

#endif USELESS_CORE_NATIVE_IO_BINARY_READER_STL_MAP_INCLUDED