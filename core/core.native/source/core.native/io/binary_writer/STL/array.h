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
	namespace binary_write_helper
	{
		template<typename Archive, typename Type, size_t _Size>
		void write_member( Archive& bw, const std::array<Type, _Size>& val, std::true_type )
		{
			bw.write( &val[ 0 ], sizeof( Type ) * _Size );
		}

		template<typename Archive, typename Type, size_t _Size>
		void write_member( Archive& bw, const std::array<Type, _Size>& val, std::false_type )
		{
			for( size_t i = 0; i < _Size; ++i )
			{
				bw.write( val[ i ] );
			}
		}

		template<typename Archive, typename Type, size_t _Size>
		void write_member( Archive& bw, const std::array<Type, _Size>& val )
		{
			typedef typename std::is_arithmetic<typename std::remove_const<Type>::type> use_optimized;
			write_member( bw, val, use_optimized() );
		}

		template<typename Archive, typename Type, size_t _Size>
		void invoke( Archive& bw, const std::array<Type, _Size>& val )
		{
			unsigned long count = static_cast< unsigned long >( _Size );
			bw.write( &count, sizeof( unsigned long ) );
			write_member( bw, val );
		}
	}
}

#endif //USELESS_CORE_NATIVE_IO_BINARY_WRITER_STL_ARRAY_INCLUDED