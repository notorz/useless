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
	namespace binary_write_helper
	{
		template<typename Archive, typename U, typename Allocator>
		void write_member( Archive& bw, const std::list<U, Allocator>& val )
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

		template<typename Archive, typename U, typename Allocator>
		void invoke( Archive& bw, const std::list<U, Allocator>& val )
		{
			unsigned long count = static_cast< unsigned long >( val.size() );
			bw.write( &count, sizeof( unsigned long ) );
			write_member( bw, val );
		}

		template<typename Archive, typename U, typename Allocator>
		void write_member( Archive& bw, const std::forward_list<U, Allocator>& val )
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

		template<typename Archive, typename U, typename Allocator>
		void invoke( Archive& bw, const std::forward_list<U, Allocator>& val )
		{
			unsigned long count = 0;
			if( !val.empty() )
			{
				auto endit = val.end();
				for( auto it = val.begin(); it != endit; ++it )
				{
					++count;
				}
			}

			bw.write( &count, sizeof( unsigned long ) );
			write_member( bw, val );
		}
	}
}

#endif USELESS_CORE_NATIVE_IO_BINARY_WRITER_STL_LIST_INCLUDED