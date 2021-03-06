//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_IO_BINARY_WRITER_STL_STRING_INCLUDED
#define USELESS_CORE_NATIVE_IO_BINARY_WRITER_STL_STRING_INCLUDED

#include <string>

namespace useless
{
    template<typename Allocator>
	struct binary_write_helper<std::basic_string<char, Allocator>>
	{
		template<typename Archive>
		static void write_member( Archive& bw, const std::basic_string<char, Allocator>& val, uint32_t count )
		{
			if( !val.empty() )
			{
				bw.write( &val[ 0 ], count );
			}
		}

		template<typename Archive>
		static void invoke( Archive& bw, const std::basic_string<char, Allocator>& val )
		{
			std::string temp = encoding::convert( bw.encoding(), encoding::utf8(), val ).buffer();
			uint32_t count = static_cast< uint32_t >( temp.size() );
			bw.write( &count, sizeof( uint32_t ) );
			write_member( bw, temp, count );
		}
    };

    template<typename Allocator>
    struct binary_write_helper<std::basic_string<wchar_t, Allocator>>
    {
        template<typename Archive>
        static void write_member( Archive& bw, const std::string& val, uint32_t count )
        {
            if( !val.empty() )
            {
                bw.write( &val[ 0 ], count );
            }
        }
        
		template<typename Archive>
		static void invoke( Archive& bw, const std::basic_string<wchar_t, Allocator>& val )
		{
			std::string temp = encoding::utf8().from_wide( val ).buffer();
			uint32_t count = static_cast< uint32_t >( temp.size() );
			bw.write( &count, sizeof( uint32_t ) );
			write_member( bw, temp, count );
		}
    };
}

#endif //USELESS_CORE_NATIVE_IO_BINARY_WRITER_STL_STRING_INCLUDED