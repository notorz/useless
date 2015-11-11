//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#ifndef USELESS_CORE_NATIVE_IO_BINARY_READER_STL_STRING_INCLUDED
#define USELESS_CORE_NATIVE_IO_BINARY_READER_STL_STRING_INCLUDED

#include <string>

namespace useless
{
    template<typename Allocator>
	struct binary_read_helper<std::basic_string<char, Allocator>>
	{
		template<typename Archive>
		static void read_member( Archive& br, std::basic_string<char, Allocator>& val, unsigned long count )
		{
			if( !val.empty() )
			{
				br.read( &val[ 0 ], count );
			}
		}

		template<typename Archive>
		static void invoke( Archive& br, std::basic_string<char, Allocator>& val )
		{
			unsigned long count;
			br.read( &count, sizeof( unsigned long ) );

			std::string temp;
			temp.resize( count );
			read_member( br, temp, count );

			val = encoding::convert( encoding::utf8(), br.encoding(), temp ).buffer();
		}
    };

    template<typename Allocator>
    struct binary_read_helper<std::basic_string<wchar_t, Allocator>>
    {
        template<typename Archive>
        static void read_member( Archive& br, std::string& val, unsigned long count )
        {
            if( !val.empty() )
            {
                br.read( &val[ 0 ], count );
            }
        }
        
		template<typename Archive>
		static void invoke( Archive& br, std::basic_string<wchar_t, Allocator>& val )
		{
			unsigned long count;
			br.read( &count, sizeof( unsigned long ) );

			std::string temp;
			temp.resize( count );
			read_member( br, temp, count );

			val = encoding::utf8().to_wide( temp ).buffer();
		}
    };
}

#endif //USELESS_CORE_NATIVE_IO_BINARY_READER_STL_STRING_INCLUDED