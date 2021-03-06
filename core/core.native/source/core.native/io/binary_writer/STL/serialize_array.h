//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_IO_BINARY_WRITER_STL_ARRAY_INCLUDED
#define USELESS_CORE_NATIVE_IO_BINARY_WRITER_STL_ARRAY_INCLUDED

#include <type_traits>
#include <array>

namespace useless
{
    template<typename Type, size_t _Size>
	struct binary_write_helper<std::array<Type, _Size>>
	{
		template<typename Archive>
		static void write_member( Archive& bw, const std::array<Type, _Size>& val, std::true_type )
		{
			bw.write( &val[ 0 ], sizeof( Type ) * _Size );
		}

		template<typename Archive>
		static void write_member( Archive& bw, const std::array<Type, _Size>& val, std::false_type )
		{
			for( size_t i = 0; i < _Size; ++i )
			{
				bw.write( val[ i ] );
			}
		}

		template<typename Archive>
		static void write_member( Archive& bw, const std::array<Type, _Size>& val )
		{
			typedef typename std::is_arithmetic<typename std::remove_const<Type>::type> use_optimized;
			write_member( bw, val, use_optimized() );
		}

		template<typename Archive>
		static void invoke( Archive& bw, const std::array<Type, _Size>& val )
		{
			uint32_t count = static_cast< uint32_t >( _Size );
			bw.write( &count, sizeof( uint32_t ) );
			write_member( bw, val );
		}
	};
}

#endif //USELESS_CORE_NATIVE_IO_BINARY_WRITER_STL_ARRAY_INCLUDED