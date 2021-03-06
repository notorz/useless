//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_IO_BINARY_READER_STL_ARRAY_INCLUDED
#define USELESS_CORE_NATIVE_IO_BINARY_READER_STL_ARRAY_INCLUDED

#include <type_traits>
#include <array>

namespace useless
{
    template<typename Type, size_t _Size>
	struct binary_read_helper<std::array<Type, _Size>>
	{
		template<typename Archive>
		static void read_member( Archive& br, std::array<Type, _Size>& val, uint32_t count, std::true_type )
		{
			br.read( &val[ 0 ], sizeof( Type ) * count );
		}

		template<typename Archive>
		static void read_member( Archive& br, std::array<Type, _Size>& val, uint32_t count, std::false_type )
		{
			for( uint32_t i = 0; i < count; ++i )
			{
				br.read( val[ i ] );
			}
		}

		template<typename Archive>
		static void read_member( Archive& br, std::array<Type, _Size>& val, uint32_t count )
		{
			if( !val.empty() )
			{
				typedef typename std::is_arithmetic<typename std::remove_const<Type>::type> use_optimized;
				read_member( br, val, count, use_optimized() );
			}
		}

		template<typename Archive>
		static void drop_member( Archive& br, Type* temp, uint32_t count, std::true_type )
		{
			br.read( &temp[ 0 ], sizeof( Type ) * count );
		}

		template<typename Archive>
		static void drop_member( Archive& br, Type* temp, uint32_t count, std::false_type )
		{
			for( uint32_t i = 0; i < count; ++i )
			{
				br.read( temp[ i ] );
			}
		}

		template<typename Archive>
		static void drop_member( Archive& br, Type* temp, uint32_t count )
		{
			if( count > 0 )
			{
				typedef typename std::is_arithmetic<typename std::remove_const<Type>::type> use_optimized;
				drop_member( br, &temp[ 0 ], count, use_optimized() );
			}
		}

		template<typename Archive>
		static void invoke( Archive& br, std::array<Type, _Size>& val )
		{
			uint32_t count;
			br.read( &count, sizeof( uint32_t ) );
			
			uint32_t dest_count = static_cast< uint32_t >( _Size );
			if( count > dest_count )
			{
				read_member( br, &val[ 0 ], dest_count );

				uint32_t temp_count = count - dest_count;
				std::vector<Type> temp;
				temp.resize( temp_count );
				drop_member( br, &temp[ 0 ], temp_count );
			}
			else
			{
				read_member( br, &val[ 0 ], count );
			}
		}
    };
}

#endif //USELESS_CORE_NATIVE_IO_BINARY_READER_STL_ARRAY_INCLUDED