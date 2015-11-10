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
	namespace binary_write_helper
	{
		template<typename Archive, typename Allocator>
		void write_member( Archive& bw, const std::basic_string<char, Allocator>& val, unsigned long count )
		{
			if( !val.empty() )
			{
				bw.write( &val[ 0 ], count );
			}
		}

		template<typename Archive, typename Allocator>
		void invoke( Archive& bw, const std::basic_string<char, Allocator>& val )
		{
			std::string temp = encoding::convert( bw.encoding(), encoding::utf8(), val ).buffer();
			unsigned long count = static_cast< unsigned long >( temp.size() );
			bw.write( &count, sizeof( unsigned long ) );
			write_member( bw, temp, count );
		}

		template<typename Archive, typename Allocator>
		void invoke( Archive& bw, const std::basic_string<wchar_t, Allocator>& val )
		{
			std::string temp = encoding::utf8().from_wide( val ).buffer();
			unsigned long count = static_cast< unsigned long >( temp.size() );
			bw.write( &count, sizeof( unsigned long ) );
			write_member( bw, temp, count );
		}
	}
}

#endif //USELESS_CORE_NATIVE_IO_BINARY_WRITER_STL_STRING_INCLUDED