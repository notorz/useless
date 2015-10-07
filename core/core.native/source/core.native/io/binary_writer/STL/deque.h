//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_IO_BINARY_WRITER_STL_DEQUE_INCLUDED
#define USELESS_CORE_NATIVE_IO_BINARY_WRITER_STL_DEQUE_INCLUDED

#include <type_traits>
#include <deque>

namespace useless
{
	namespace binary_write_helper
	{
		template<typename Archive, typename U, typename Allocator>
		void write_member( Archive& bw, const std::deque<U, Allocator>& val, unsigned long count, std::true_type )
		{
			bw.write( &val[ 0 ], sizeof( U ) * count );
		}

		template<typename Archive, typename U, typename Allocator>
		void write_member( Archive& bw, const std::deque<U, Allocator>& val, unsigned long count, std::false_type )
		{
			for( unsigned long i = 0; i < count; ++i )
			{
				bw.write( val[ i ] );
			}
		}

		template<typename Archive, typename U, typename Allocator>
		void write_member( Archive& bw, const std::deque<U, Allocator>& val, unsigned long count )
		{
			if( !val.empty() )
			{
				typedef typename std::is_arithmetic<typename std::remove_const<U>::type> use_optimized;
				write_member( bw, val, count, use_optimized() );
			}
		}

		// bool Æ¯¼öÈ­
		template<typename Archive, typename Allocator>
		void write_member( Archive& bw, const std::deque<bool, Allocator>& val, unsigned long count )
		{
			if( !val.empty() )
			{
				for( unsigned long i = 0; i < count; ++i )
				{
					char temp = val[ i ] ? 1 : 0;
					bw.write( &temp, sizeof( char ) );
				}
			}
		}

		template<typename Archive, typename U, typename Allocator>
		void invoke( Archive& bw, const std::deque<U, Allocator>& val )
		{
			unsigned long count = static_cast< unsigned long >( val.size() );
			bw.write( &count, sizeof( unsigned long ) );
			write_member( bw, val, count );
		}
	}
}

#endif USELESS_CORE_NATIVE_IO_BINARY_WRITER_STL_DEQUE_INCLUDED