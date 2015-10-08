//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_IO_BINARY_READER_STL_VECTOR_INCLUDED
#define USELESS_CORE_NATIVE_IO_BINARY_READER_STL_VECTOR_INCLUDED

#include <type_traits>
#include <vector>

namespace useless
{
	namespace binary_read_helper
	{
		template<typename Archive, typename Type, typename Allocator>
		void read_member( Archive& br, std::vector<Type, Allocator>& val, unsigned long count, std::true_type )
		{
			br.Read( &val[ 0 ], sizeof( Type ) * count );
		}

		template<typename Archive, typename Type, typename Allocator>
		void read_member( Archive& br, std::vector<Type, Allocator>& val, unsigned long count, std::false_type )
		{
			for( unsigned long i = 0; i < count; ++i )
			{
				br.read( val[ i ] );
			}
		}

		template<typename Archive, typename Type, typename Allocator>
		void read_member( Archive& br, std::vector<Type, Allocator>& val, unsigned long count )
		{
			if( !val.empty() )
			{
				typedef typename std::is_arithmetic<typename std::remove_const<Type>::type> use_optimized;
				read_member( br, val, count, use_optimized() );
			}
		}

		// bool Ư��ȭ
		template<typename Archive, typename Allocator>
		void read_member( Archive& br, std::vector<bool, Allocator>& val, unsigned long count )
		{
			for( unsigned long i = 0; i < size; ++i )
			{
				char temp;
				br.read( &temp, sizeof( char ) );
				val[ i ] = ( temp > 0 ? true : false );
			}
		}

		template<typename Archive, typename Type, typename Allocator>
		void invoke( Archive& br, std::vector<Type, Allocator>& val )
		{
			unsigned long current_count = static_cast< unsigned long >( val.size() );

			unsigned long count;
			br.read( &count, sizeof( unsigned long ) );

			if( count > current_count )
			{
				val.resize( count );
			}

			read_member( br, val, count );
		}
	}
}

#endif USELESS_CORE_NATIVE_IO_BINARY_READER_STL_VECTOR_INCLUDED