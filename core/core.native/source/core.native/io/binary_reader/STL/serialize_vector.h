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
    template<typename Type, typename Allocator>
	struct binary_read_helper<std::vector<Type, Allocator>>
	{
		template<typename Archive>
		static void read_member( Archive& br, std::vector<Type, Allocator>& val, uint32_t count, std::true_type )
		{
			br.Read( &val[ 0 ], sizeof( Type ) * count );
		}

		template<typename Archive>
		static void read_member( Archive& br, std::vector<Type, Allocator>& val, uint32_t count, std::false_type )
		{
			for( uint32_t i = 0; i < count; ++i )
			{
				br.read( val[ i ] );
			}
		}

		template<typename Archive>
		static void read_member( Archive& br, std::vector<Type, Allocator>& val, uint32_t count )
		{
			if( !val.empty() )
			{
				typedef typename std::is_arithmetic<typename std::remove_const<Type>::type> use_optimized;
				read_member( br, val, count, use_optimized() );
			}
		}

		// bool Æ¯¼öÈ­
		template<typename Archive>
		static void read_member( Archive& br, std::vector<bool, Allocator>& val, uint32_t count )
		{
			for( uint32_t i = 0; i < count; ++i )
			{
				char temp;
				br.read( &temp, sizeof( char ) );
				val[ i ] = ( temp > 0 ? true : false );
			}
		}

		template<typename Archive>
		static void invoke( Archive& br, std::vector<Type, Allocator>& val )
		{
			uint32_t current_count = static_cast< uint32_t >( val.size() );

			uint32_t count;
			br.read( &count, sizeof( uint32_t ) );

			if( count > current_count )
			{
				val.resize( count );
			}

			read_member( br, val, count );
		}
    };
    
    template<typename Allocator>
    struct binary_read_helper<std::vector<bool, Allocator>>
    {
        template<typename Archive>
        static void read_member( Archive& br, std::vector<bool, Allocator>& val, uint32_t count )
        {
            for( uint32_t i = 0; i < count; ++i )
            {
                char temp;
                br.read( &temp, sizeof( char ) );
                val[ i ] = ( temp > 0 ? true : false );
            }
        }
        
        template<typename Archive>
        static void invoke( Archive& br, std::vector<bool, Allocator>& val )
        {
			uint32_t current_count = static_cast< uint32_t >( val.size() );
            
            uint32_t count;
            br.read( &count, sizeof( uint32_t ) );
            
            if( count > current_count )
            {
                val.resize( count );
            }
            
            read_member( br, val, count );
        }
    };
}

#endif //USELESS_CORE_NATIVE_IO_BINARY_READER_STL_VECTOR_INCLUDED