//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>

#include "core.native/io.h"

using namespace useless;

bool test_constructor_and_destructor()
{
	{
		fixed_stream stream1( 32 );
		binary_writer writer_test( stream1 );
		writer_test.write_s32( 45 );

		binary_reader reader_test( stream1.raw_data(), stream1.size() );
		int32_t read_data = reader_test.read_s32();

		if( read_data != 45 )
		{
			return false;
		}
	}

	{
		binary_writer writer_test( "binary_writer_and_reader_test.txt", openmode::out );
		writer_test.write_s32( 45 );
		writer_test.close();

		binary_reader reader_test( "binary_writer_and_reader_test.txt", openmode::in );
		int32_t read_data = reader_test.read_s32();
		reader_test.close();

		if( read_data != 45 )
		{
			::remove( "binary_writer_and_reader_test.txt" );
			return false;
		}

		::remove( "binary_writer_and_reader_test.txt" );
	}

	{
		uint8_t* temp_memory = new uint8_t[ 32 ];
		binary_writer writer_test( temp_memory, 32 );
		writer_test.write_s32( 45 );

		binary_reader reader_test( temp_memory, 32 );
		int32_t read_data = reader_test.read_s32();

		if( read_data != 45 )
		{
			delete[] temp_memory;
			return false;
		}

		delete[] temp_memory;
	}

	{
		binary_writer writer_test( 32 );
		writer_test.write_s32( 45 );

		binary_reader reader_test( writer_test.stream()->raw_data(), 32 );
		int32_t read_data = reader_test.read_s32();

		if( read_data != 45 )
		{
			return false;
		}
	}

	return true;
}

bool test_set_and_get_stream()
{
	binary_writer writer_test;
	fixed_stream stream1( 32 );
	writer_test.stream( stream1 );

	if( writer_test.stream() != &stream1 )
	{
		return false;
	}

	return true;
}

bool test_write_and_read()
{
	{
		binary_writer writer_test( "binary_write_and_read_test.txt", openmode::out );
		writer_test.write_u8( std::numeric_limits<uint8_t>::min() );
		writer_test.write_u8( std::numeric_limits<uint8_t>::max() );
		writer_test.write_u8( std::numeric_limits<uint8_t>::epsilon() );
		writer_test.write_s8( std::numeric_limits<int8_t>::min() );
		writer_test.write_s8( std::numeric_limits<int8_t>::max() );
		writer_test.write_s8( std::numeric_limits<int8_t>::epsilon() );
		writer_test.write_u16( std::numeric_limits<uint16_t>::min() );
		writer_test.write_u16( std::numeric_limits<uint16_t>::max() );
		writer_test.write_u16( std::numeric_limits<uint16_t>::epsilon() );
		writer_test.write_s16( std::numeric_limits<int16_t>::min() );
		writer_test.write_s16( std::numeric_limits<int16_t>::max() );
		writer_test.write_s16( std::numeric_limits<int16_t>::epsilon() );
		writer_test.write_u32( std::numeric_limits<uint32_t>::min() );
		writer_test.write_u32( std::numeric_limits<uint32_t>::max() );
		writer_test.write_u32( std::numeric_limits<uint32_t>::epsilon() );
		writer_test.write_s32( std::numeric_limits<int32_t>::min() );
		writer_test.write_s32( std::numeric_limits<int32_t>::max() );
		writer_test.write_s32( std::numeric_limits<int32_t>::epsilon() );
		writer_test.write_u64( std::numeric_limits<uint64_t>::min() );
		writer_test.write_u64( std::numeric_limits<uint64_t>::max() );
		writer_test.write_u64( std::numeric_limits<uint64_t>::epsilon() );
		writer_test.write_s64( std::numeric_limits<int64_t>::min() );
		writer_test.write_s64( std::numeric_limits<int64_t>::max() );
		writer_test.write_s64( std::numeric_limits<int64_t>::epsilon() );
		writer_test.write_f32( std::numeric_limits<float>::min() );
		writer_test.write_f32( std::numeric_limits<float>::max() );
		writer_test.write_f32( std::numeric_limits<float>::epsilon() );
		writer_test.write_f64( std::numeric_limits<double>::min() );
		writer_test.write_f64( std::numeric_limits<double>::max() );
		writer_test.write_f64( std::numeric_limits<double>::epsilon() );
		writer_test.write_string( "useless" );
		writer_test.write_string( L"binary writer test" );
		writer_test.write_string( string_ansi( "write_string_ansi test" ) );
		writer_test.write_string( string_wide( L"write_string_wide test" ) );
		writer_test.write_bool( true );

		writer_test << "ansi string operator test";
		writer_test << L"wide string operator test";
		float val = 3.423f;
		writer_test << val;
		writer_test.close();

		binary_reader reader_test( "binary_write_and_read_test.txt", openmode::in );
		uint8_t uint8_min = reader_test.read_u8();
		uint8_t uint8_max = reader_test.read_u8();
		uint8_t uint8_epsilon = reader_test.read_u8();
		int8_t int8_min = reader_test.read_s8();
		int8_t int8_max = reader_test.read_s8();
		int8_t int8_epsilon = reader_test.read_s8();
		uint16_t uint16_min = reader_test.read_u16();
		uint16_t uint16_max = reader_test.read_u16();
		uint16_t uint16_epsilon = reader_test.read_u16();
		int16_t int16_min = reader_test.read_s16();
		int16_t int16_max = reader_test.read_s16();
		int16_t int16_epsilon = reader_test.read_s16();
		uint32_t uint32_min = reader_test.read_u32();
		uint32_t uint32_max = reader_test.read_u32();
		uint32_t uint32_epsilon = reader_test.read_u32();
		int32_t int32_min = reader_test.read_s32();
		int32_t int32_max = reader_test.read_s32();
		int32_t int32_epsilon = reader_test.read_s32();
		uint64_t uint64_min = reader_test.read_u64();
		uint64_t uint64_max = reader_test.read_u64();
		uint64_t uint64_epsilon = reader_test.read_u64();
		int64_t int64_min = reader_test.read_s64();
		int64_t int64_max = reader_test.read_s64();
		int64_t int64_epsilon = reader_test.read_s64();
		float f32_min = reader_test.read_f32();
		float f32_max = reader_test.read_f32();
		float f32_epsilon = reader_test.read_f32();
		double f64_min = reader_test.read_f64();
		double f64_max = reader_test.read_f64();
		double f64_epsilon = reader_test.read_f64();
		string_ansi read_str1 = reader_test.read_string_ansi();
		string_wide read_str2 = reader_test.read_string_wide();
		string_ansi read_str3 = reader_test.read_string_ansi();
		string_wide read_str4 = reader_test.read_string_wide();
		bool boolean = reader_test.read_bool();

		string_ansi read_str5;		reader_test >> read_str5;
		string_wide read_str6;		reader_test >> read_str6;
		float temp_float;		reader_test >> temp_float;
		reader_test.close();

		if( uint8_min != std::numeric_limits<uint8_t>::min() ||
			uint8_max != std::numeric_limits<uint8_t>::max() ||
			uint8_epsilon != std::numeric_limits<uint8_t>::epsilon() ||
			int8_min != std::numeric_limits<int8_t>::min() ||
			int8_max != std::numeric_limits<int8_t>::max() ||
			int8_epsilon != std::numeric_limits<int8_t>::epsilon() ||
			uint16_min != std::numeric_limits<uint16_t>::min() ||
			uint16_max != std::numeric_limits<uint16_t>::max() ||
			uint16_epsilon != std::numeric_limits<uint16_t>::epsilon() ||
			int16_min != std::numeric_limits<int16_t>::min() ||
			int16_max != std::numeric_limits<int16_t>::max() ||
			int16_epsilon != std::numeric_limits<int16_t>::epsilon() ||
			uint32_min != std::numeric_limits<uint32_t>::min() ||
			uint32_max != std::numeric_limits<uint32_t>::max() ||
			uint32_epsilon != std::numeric_limits<uint32_t>::epsilon() ||
			int32_min != std::numeric_limits<int32_t>::min() ||
			int32_max != std::numeric_limits<int32_t>::max() ||
			int32_epsilon != std::numeric_limits<int32_t>::epsilon() ||
			uint64_min != std::numeric_limits<uint64_t>::min() ||
			uint64_max != std::numeric_limits<uint64_t>::max() ||
			uint64_epsilon != std::numeric_limits<uint64_t>::epsilon() ||
			int64_min != std::numeric_limits<int64_t>::min() ||
			int64_max != std::numeric_limits<int64_t>::max() ||
			int64_epsilon != std::numeric_limits<int64_t>::epsilon() ||
			f32_min != std::numeric_limits<float>::min() ||
			f32_max != std::numeric_limits<float>::max() ||
			f32_epsilon != std::numeric_limits<float>::epsilon() ||
			f64_min != std::numeric_limits<double>::min() ||
			f64_max != std::numeric_limits<double>::max() ||
			f64_epsilon != std::numeric_limits<double>::epsilon() ||
			read_str1 != "useless" ||
			read_str2 != L"binary writer test" ||
			read_str3 != "write_string_ansi test" ||
			read_str4 != L"write_string_wide test" ||
			boolean != true ||
			read_str5 != "ansi string operator test" ||
			read_str6 != L"wide string operator test" ||
			temp_float != 3.423f )
		{
			::remove( "binary_write_and_read_test.txt" );
			return false;
		}

		::remove( "binary_write_and_read_test.txt" );
	}

	{
		binary_writer writer_test( 1024 );
		writer_test.write_u8( std::numeric_limits<uint8_t>::min() );
		writer_test.write_u8( std::numeric_limits<uint8_t>::max() );
		writer_test.write_u8( std::numeric_limits<uint8_t>::epsilon() );
		writer_test.write_s8( std::numeric_limits<int8_t>::min() );
		writer_test.write_s8( std::numeric_limits<int8_t>::max() );
		writer_test.write_s8( std::numeric_limits<int8_t>::epsilon() );
		writer_test.write_u16( std::numeric_limits<uint16_t>::min() );
		writer_test.write_u16( std::numeric_limits<uint16_t>::max() );
		writer_test.write_u16( std::numeric_limits<uint16_t>::epsilon() );
		writer_test.write_s16( std::numeric_limits<int16_t>::min() );
		writer_test.write_s16( std::numeric_limits<int16_t>::max() );
		writer_test.write_s16( std::numeric_limits<int16_t>::epsilon() );
		writer_test.write_u32( std::numeric_limits<uint32_t>::min() );
		writer_test.write_u32( std::numeric_limits<uint32_t>::max() );
		writer_test.write_u32( std::numeric_limits<uint32_t>::epsilon() );
		writer_test.write_s32( std::numeric_limits<int32_t>::min() );
		writer_test.write_s32( std::numeric_limits<int32_t>::max() );
		writer_test.write_s32( std::numeric_limits<int32_t>::epsilon() );
		writer_test.write_u64( std::numeric_limits<uint64_t>::min() );
		writer_test.write_u64( std::numeric_limits<uint64_t>::max() );
		writer_test.write_u64( std::numeric_limits<uint64_t>::epsilon() );
		writer_test.write_s64( std::numeric_limits<int64_t>::min() );
		writer_test.write_s64( std::numeric_limits<int64_t>::max() );
		writer_test.write_s64( std::numeric_limits<int64_t>::epsilon() );
		writer_test.write_f32( std::numeric_limits<float>::min() );
		writer_test.write_f32( std::numeric_limits<float>::max() );
		writer_test.write_f32( std::numeric_limits<float>::epsilon() );
		writer_test.write_f64( std::numeric_limits<double>::min() );
		writer_test.write_f64( std::numeric_limits<double>::max() );
		writer_test.write_f64( std::numeric_limits<double>::epsilon() );
		writer_test.write_string( "useless" );
		writer_test.write_string( L"binary writer test" );
		writer_test.write_string( string_ansi( "write_string_ansi test" ) );
		writer_test.write_string( string_wide( L"write_string_wide test" ) );
		writer_test.write_bool( true );

		writer_test << "ansi string operator test";
		writer_test << L"wide string operator test";
		float val = 3.423f;
		writer_test << val;

		binary_reader reader_test( writer_test.stream()->raw_data(), writer_test.stream()->size() );
		uint8_t uint8_min = reader_test.read_u8();
		uint8_t uint8_max = reader_test.read_u8();
		uint8_t uint8_epsilon = reader_test.read_u8();
		int8_t int8_min = reader_test.read_s8();
		int8_t int8_max = reader_test.read_s8();
		int8_t int8_epsilon = reader_test.read_s8();
		uint16_t uint16_min = reader_test.read_u16();
		uint16_t uint16_max = reader_test.read_u16();
		uint16_t uint16_epsilon = reader_test.read_u16();
		int16_t int16_min = reader_test.read_s16();
		int16_t int16_max = reader_test.read_s16();
		int16_t int16_epsilon = reader_test.read_s16();
		uint32_t uint32_min = reader_test.read_u32();
		uint32_t uint32_max = reader_test.read_u32();
		uint32_t uint32_epsilon = reader_test.read_u32();
		int32_t int32_min = reader_test.read_s32();
		int32_t int32_max = reader_test.read_s32();
		int32_t int32_epsilon = reader_test.read_s32();
		uint64_t uint64_min = reader_test.read_u64();
		uint64_t uint64_max = reader_test.read_u64();
		uint64_t uint64_epsilon = reader_test.read_u64();
		int64_t int64_min = reader_test.read_s64();
		int64_t int64_max = reader_test.read_s64();
		int64_t int64_epsilon = reader_test.read_s64();
		float f32_min = reader_test.read_f32();
		float f32_max = reader_test.read_f32();
		float f32_epsilon = reader_test.read_f32();
		double f64_min = reader_test.read_f64();
		double f64_max = reader_test.read_f64();
		double f64_epsilon = reader_test.read_f64();
		string_ansi read_str1 = reader_test.read_string_ansi();
		string_wide read_str2 = reader_test.read_string_wide();
		string_ansi read_str3 = reader_test.read_string_ansi();
		string_wide read_str4 = reader_test.read_string_wide();
		bool boolean = reader_test.read_bool();

		string_ansi read_str5;		reader_test >> read_str5;
		string_wide read_str6;		reader_test >> read_str6;
		float temp_float;		reader_test >> temp_float;

		if( uint8_min != std::numeric_limits<uint8_t>::min() ||
			uint8_max != std::numeric_limits<uint8_t>::max() ||
			uint8_epsilon != std::numeric_limits<uint8_t>::epsilon() ||
			int8_min != std::numeric_limits<int8_t>::min() ||
			int8_max != std::numeric_limits<int8_t>::max() ||
			int8_epsilon != std::numeric_limits<int8_t>::epsilon() ||
			uint16_min != std::numeric_limits<uint16_t>::min() ||
			uint16_max != std::numeric_limits<uint16_t>::max() ||
			uint16_epsilon != std::numeric_limits<uint16_t>::epsilon() ||
			int16_min != std::numeric_limits<int16_t>::min() ||
			int16_max != std::numeric_limits<int16_t>::max() ||
			int16_epsilon != std::numeric_limits<int16_t>::epsilon() ||
			uint32_min != std::numeric_limits<uint32_t>::min() ||
			uint32_max != std::numeric_limits<uint32_t>::max() ||
			uint32_epsilon != std::numeric_limits<uint32_t>::epsilon() ||
			int32_min != std::numeric_limits<int32_t>::min() ||
			int32_max != std::numeric_limits<int32_t>::max() ||
			int32_epsilon != std::numeric_limits<int32_t>::epsilon() ||
			uint64_min != std::numeric_limits<uint64_t>::min() ||
			uint64_max != std::numeric_limits<uint64_t>::max() ||
			uint64_epsilon != std::numeric_limits<uint64_t>::epsilon() ||
			int64_min != std::numeric_limits<int64_t>::min() ||
			int64_max != std::numeric_limits<int64_t>::max() ||
			int64_epsilon != std::numeric_limits<int64_t>::epsilon() ||
			f32_min != std::numeric_limits<float>::min() ||
			f32_max != std::numeric_limits<float>::max() ||
			f32_epsilon != std::numeric_limits<float>::epsilon() ||
			f64_min != std::numeric_limits<double>::min() ||
			f64_max != std::numeric_limits<double>::max() ||
			f64_epsilon != std::numeric_limits<double>::epsilon() ||
			read_str1 != "useless" ||
			read_str2 != L"binary writer test" ||
			read_str3 != "write_string_ansi test" ||
			read_str4 != L"write_string_wide test" ||
			boolean != true ||
			read_str5 != "ansi string operator test" ||
			read_str6 != L"wide string operator test" ||
			temp_float != 3.423f )
		{
			return false;
		}
	}

	return true;
}

int main()
{
	printf( "test_constructor_and_destructor - %s\n",	test_constructor_and_destructor() ? "ok" : "failed" );
	printf( "test_set_and_get_stream - %s\n",			test_set_and_get_stream() ? "ok" : "failed" );
	printf( "test_write_and_read - %s\n",				test_write_and_read() ? "ok" : "failed" );

	return 0;
}