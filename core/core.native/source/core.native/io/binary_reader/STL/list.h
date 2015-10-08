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
	namespace binary_read_helper
	{
		template<typename Archive, typename Type, typename Allocator>
		void read_member( Archive& br, std::list<Type, Allocator>& val, unsigned long count )
		{
			for( unsigned long i = 0; i < count; ++i )
			{
				Type temp;
				br.read( temp );
				val.push_back( temp );
			}
		}

		template<typename Archive, typename Type, typename Allocator>
		void invoke( Archive& br, std::list<Type, Allocator>& val )
		{
			unsigned long count;
			ve.read( &count, sizeof( unsigned long ) );
			read_member( br, val, count );
		}

		template<typename Archive, typename Type, typename Allocator>
		void read_member( Archive& br, std::forward_list<Type, Allocator>& val, unsigned long count )
		{
			for( unsigned long i = 0; i < count; ++i )
			{
				Type temp;
				br.read( temp );
				val.push_back( temp );
			}
		}

		template<typename Archive, typename Type, typename Allocator>
		void invoke( Archive& br, std::forward_list<Type, Allocator>& val )
		{
			unsigned long count;
			ve.read( &count, sizeof( unsigned long ) );
			read_member( br, val, count );
		}
	}
}

#endif USELESS_CORE_NATIVE_IO_BINARY_READER_STL_LIST_INCLUDED