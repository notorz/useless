//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_IO_BINARY_WRITER_STL_VECTOR_INCLUDED
#define USELESS_CORE_NATIVE_IO_BINARY_WRITER_STL_VECTOR_INCLUDED

#include <type_traits>
#include <vector>

namespace useless
{
    template<typename Type, typename Allocator>
	struct binary_write_helper<std::vector<Type, Allocator>>
	{
		template<typename Archive>
		static void write_member( Archive& bw, const std::vector<Type, Allocator>& val, uint32_t count, std::true_type )
		{
			bw.write( &val[ 0 ], sizeof( Type ) * count );
		}

		template<typename Archive>
		static void write_member( Archive& bw, const std::vector<Type, Allocator>& val, uint32_t count, std::false_type )
		{
			for( uint32_t i = 0; i < count; ++i )
			{
				bw.write( val[ i ] );
			}
		}

		template<typename Archive>
		static void write_member( Archive& bw, const std::vector<Type, Allocator>& val, uint32_t count )
		{
			if( !val.empty() )
			{
				typedef typename std::is_arithmetic<typename std::remove_const<Type>::type> use_optimized;
				write_member( bw, val, count, use_optimized() );
			}
		}

		// bool Ư��ȭ
		template<typename Archive>
		static void write_member( Archive& bw, const std::vector<bool, Allocator>& val, uint32_t count )
		{
			if( !val.empty() )
			{
				for( uint32_t i = 0; i < count; ++i )
				{
					char temp = val[ i ] ? 1 : 0;
					bw.write( &temp, sizeof( char ) );
				}
			}
		}

		template<typename Archive>
		static void invoke( Archive& bw, const std::vector<Type, Allocator>& val )
		{
			uint32_t count = static_cast< uint32_t >( val.size() );
			bw.write( &count, sizeof( uint32_t ) );
			write_member( bw, val, count );
		}
    };
    
    template<typename Allocator>
    struct binary_write_helper<std::vector<bool, Allocator>>
    {   
        template<typename Archive>
        static void write_member( Archive& bw, const std::vector<bool, Allocator>& val, uint32_t count )
        {
            if( !val.empty() )
            {
                for( uint32_t i = 0; i < count; ++i )
                {
                    char temp = val[ i ] ? 1 : 0;
                    bw.write( &temp, sizeof( char ) );
                }
            }
        }
        
        template<typename Archive>
        static void invoke( Archive& bw, const std::vector<bool, Allocator>& val )
        {
            uint32_t count = static_cast< uint32_t >( val.size() );
            bw.write( &count, sizeof( uint32_t ) );
            write_member( bw, val, count );
        }
    };
}

#endif //USELESS_CORE_NATIVE_IO_BINARY_WRITER_STL_VECTOR_INCLUDED