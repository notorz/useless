//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#include <stdio.h>
#include <memory.h>
#include <map>

#include "core.native/string.h"

#ifndef TEXT
#ifdef  UNICODE
#define TEXT( quote ) L##quote
#else
#define TEXT( quote ) quote
#endif
#endif

#ifdef UNICODE
#define tmain wmain
#else
#define tmain main
#endif

using namespace useless;

void test_constructor()
{
	string str1( TEXT( 'a' ) );
	string str2( TEXT( "Test String" ) );
	string str3( TEXT( "Test" ), 3 );
	string str4( str3 );

	if( str1 == TEXT( 'a' ) &&
		str2 == TEXT( "Test String" ) &&
		str3 == TEXT( "Tes" ) &&
		str3.length() == 3 && 
		str4 == str3 )
	{
		printf( "test_constructor() - ok\n" );
	}
}

void test_is_empty()
{
	string str;

	if( str.is_empty() )
	{
		str = TEXT( "abc" );

		if( !str.is_empty() )
		{
			::printf( "test_is_empty() - ok\n" );
		}
	}
}

void test_length()
{
	string str = TEXT( "0123456789" );

	if( str.length() == 10 )
	{
		str = TEXT( "abcd" );

		if( str.length() == 4 )
		{
			::printf( "test_length() - ok\n" );
		}
	}
}

void test_resize()
{
	string str = TEXT( "0123456789" );

	str.resize( str.length() + 2, '!' );

	if( str == TEXT( "0123456789!!" ) && str.length() == 12 )
	{
		str.resize( 25 );

		if( str.length() == 25 )
		{
			::printf( "test_resize() - ok\n" );
		}
	}
}

void test_clear()
{
	string str = TEXT( "0123456789" );

	str.clear();

	if( str.is_empty() )
	{
		::printf( "test_clear() - ok\n" );
	}
}

void test_compare_operators()
{
	string str1( TEXT( "hello" ) );
	string str2( TEXT( "world!!" ) );
	string str3( TEXT( "hello" ) );

	if( str1 == str3 && 
		str1 != str2 && 
		str1 < str2 && 
		str2 > str1 && 
		str1 >= str3 && 
		str3 <= str1 && 
		str1 <= str2 && 
		str2 >= str1 )
	{
		::printf( "test_compare_operators() - ok 1\n" );
	}

	std::map<string, int> test_map;
	test_map.insert( std::pair<string, int>( TEXT( "one" ), 1 ) );
	test_map.insert( std::pair<string, int>( TEXT( "four" ), 4 ) );
	test_map.insert( std::pair<string, int>( TEXT( "two" ), 2 ) );
	test_map.insert( std::pair<string, int>( TEXT( "ten" ), 10 ) );
	test_map.insert( std::pair<string, int>( TEXT( "six" ), 6 ) );

	std::map<string, int>::iterator find_data1 = test_map.find( TEXT( "one" ) );
	std::map<string, int>::iterator find_data2 = test_map.find( TEXT( "two" ) );
	std::map<string, int>::iterator find_data3 = test_map.find( TEXT( "four" ) );
	std::map<string, int>::iterator find_data4 = test_map.find( TEXT( "six" ) );
	std::map<string, int>::iterator find_data5 = test_map.find( TEXT( "ten" ) );

	if( find_data1 != test_map.end() && 
		find_data2 != test_map.end() &&
		find_data3 != test_map.end() &&
		find_data4 != test_map.end() &&
		find_data5 != test_map.end() )
	{
		if( find_data1->second == 1 &&
			find_data2->second == 2 &&
			find_data3->second == 4 &&
			find_data4->second == 6 &&
			find_data5->second == 10 )
		{
			::printf( "test_compare_operators() - ok 2\n" );
		}
	}
}

void test_plus()
{
	string str1 = TEXT( "one" );
	string str2 = TEXT( "two" );
	string str3 = TEXT( "three" );

	if( str1 + str2 + str3 != TEXT( "onetwothree" ) )
	{
		return;
	}

	string str0 = str1 + str3;
	if( str0 != TEXT( "onethree" ) )
	{
		return;
	}

	str0 += str2;
	if( str0 != TEXT( "onethreetwo" ) )
	{
		return;
	}

	::printf( "test_plus() - ok\n" );
}

void test_array()
{
	string str = TEXT( "abcdefghigklmonop" );

	if( str[ 2 ] == TEXT( 'c' ) )
	{
		::printf( "test_array() - ok\n" );
	}
}

void test_string_format()
{
	string str = string::make_format( TEXT( "%d+%d=%d" ), 1, 2, 1 + 2 );
	if( str != TEXT( "1+2=3" ) )
	{
		return;
	}

	str.format( TEXT( "%d-%d=%d" ), 1, 2, 1 - 2 );
	if( str != TEXT( "1-2=-1" ) )
	{
		return;
	}

	::printf( "test_string_format() - ok\n" );
}

void test_trim()
{
	string str1 = TEXT( "\t\tabc\v\n" );
	str1.trim();
	if( str1 != TEXT( "abc" ) )
	{
		return;
	}

	str1 = TEXT( "\t  string trim test       \t" );
	str1.trim();
	if( str1 != TEXT( "string trim test" ) )
	{
		return;
	}

	::printf( "test_trim() - ok\n" );
}

void test_trim_left()
{
	string str1 = TEXT( "  \t \t  \t  abc" );
	string str2 = TEXT( "abc \t  \t  \t   " );

	str1.trim_left();
	str2.trim_left();

	if( str1 == TEXT( "abc" ) && str2 != TEXT( "abc" ) )
	{
		::printf( "test_trim_left() - ok\n" );
	}
}

void test_trim_right()
{
	string str1 = TEXT( "  \t \t  \t  abc" );
	string str2 = TEXT( " abc \t  \t  \t   " );

	str1.trim_right();
	str2.trim_right();

	if( str1 != TEXT( "abc" ) && str2 == TEXT( " abc" ) )
	{
		::printf( "test_trim_right() - ok\n" );
	}
}

void test_make_upper()
{
	string str1 = TEXT( "aBc#Def/GhI-" );
	string str2 = str1.make_upper();
	if( str2 == TEXT( "ABC#DEF/GHI-" ) )
	{
		::printf( "test_make_upper() - ok\n" );
	}
}

void test_make_lower()
{
	string str1 = TEXT( "aBC/dEf#ghI-" );
	string str2 = str1.make_lower();
	if( str2 == TEXT( "abc/def#ghi-" ) )
	{
		::printf( "test_make_lower() - ok\n" );
	}
}

void test_compare_no_case()
{
	string str1 = TEXT( "ABCDEFG" );
	string str2 = TEXT( "abcdefg" );

	if( str1.compare_no_case( str2 ) == 0 )
	{
		::printf( "test_compare_no_case() - ok\n" );
	}
}

void test_compare()
{
	string str1 = TEXT( "123" );
	string str2 = TEXT( "456" );
	string str3 = TEXT( "123456" );

	if( str3.compare( str1 + str2 ) != 0 || str1.compare( str2 ) == 0 )
	{
		return;
	}

	if( str3.compare( 3, 3, str2 ) != 0 || str3.compare( 3, 2, str2, 2 ) != 0 )
	{
		return;
	}

	if( str2.compare( 0, 3, str3, 3, 3 ) != 0 )
	{
		return;
	}

	::printf( "test_compare() - ok\n" );
}

void test_parse_number()
{
	string str1 = TEXT( "12345" );
	string str2 = TEXT( "12345.9" );
	string str3 = TEXT( "12345.99" );

	int str2int = str1.get_int();
	float str2float = str2.get_float();
	double str2double = str3.get_double();

	str2int += 1;
	str2float += 0.1f;
	str2double += 0.00001;

	if( str2int == 12346
		&& str2float == 12346.0f
		&& str2double == 12345.99001 )
	{
		::printf( "test_parse_number() - ok\n" );
	}
}

void test_left_right_mid()
{
	string str = TEXT( "0123456789" );
	string str_left4 = str.left( 4 );
	string str_right4 = str.right( 4 );
	string str_mid4to6 = str.mid( 4, 3 );

	if( str_left4 == TEXT( "0123" ) && str_right4 == TEXT( "6789" ) && str_mid4to6 == TEXT( "456" ) )
	{
		::printf( "test_left_right_mid() - ok\n" );
	}
}

void test_sub_string()
{
	string str1 = TEXT( "0123456789" );
	string str2 = str1.sub_string( 4, 3 );
	string str3 = str1.sub_string( 6 );

	if( str2 == TEXT( "456" ) && str3 == TEXT( "6789" ) )
	{
		::printf( "test_sub_string() - ok\n" );
	}
}

void test_find()
{
	string str1 = TEXT( "01234567890123456789" );
	size_t find_index1 = str1.find( TEXT( "456" ) );
	size_t find_index2 = str1.find( TEXT( "456" ), 6 );

	if( find_index1 != 4 || find_index2 != 14 )
	{
		return;
	}

	string find_str = TEXT( "456" );
	find_index1 = str1.find( find_str );
	find_index2 = str1.find( find_str, 6 );

	if( find_index1 != 4 || find_index2 != 14 )
	{
		return;
	}

	find_index1 = str1.find( TEXT( '3' ) );
	find_index2 = str1.find( TEXT( '3' ), 5 );

	if( find_index1 != 3 || find_index2 != 13 )
	{
		return;
	}

	str1 = TEXT( "This is a sample string for this program" );
	find_str = TEXT( "for" );
	find_index1 = str1.find( find_str, 10, 2 );

	if( find_index1 != 24 )
	{
		return;
	}

	find_index1 = str1.find( TEXT( "useless" ) );
	if( find_index1 != string::npos() )
	{
		return;
	}

	::printf( "test_find() - ok\n" );
}

void test_reverse_find()
{
	string str1 = TEXT( "01234567890123456789" );
	size_t find_index1 = str1.reverse_find( TEXT( "456" ) );
	size_t find_index2 = str1.reverse_find( TEXT( "456" ), 6 );

	if( find_index1 != 14 || find_index2 != 4 )
	{
		return;
	}

	string find_str = TEXT( "456" );
	find_index1 = str1.reverse_find( find_str );
	find_index2 = str1.reverse_find( find_str, 6 );

	if( find_index1 != 14 || find_index2 != 4 )
	{
		return;
	}

	find_index1 = str1.reverse_find( TEXT( '3' ) );
	find_index2 = str1.reverse_find( TEXT( '3' ), 12 );

	if( find_index1 != 13 || find_index2 != 3 )
	{
		return;
	}

	str1 = TEXT( "It is a nice day. I am happy" );
	find_str = TEXT( "am" );
	find_index1 = str1.reverse_find( find_str, 33, 2 );

	if( find_index1 != 20 )
	{
		return;
	}

	find_str = TEXT( "useless" );
	find_index1 = str1.reverse_find( find_str );

	if( find_index1 != string::npos() )
	{
		return;
	}

	::printf( "test_reverse_find() - ok\n" );
}

void test_replace_first()
{
	string str1 = TEXT( "I'm your lover.. I'm your lover!!" );
	str1.replace_first( TEXT( "lover" ), TEXT( "fucker" ) );

	if( str1 == TEXT( "I'm your fucker.. I'm your lover!!" ) )
	{
		::printf( "test_replace_first() - ok\n" );
	}
}

void test_replace_last()
{
	string str1 = TEXT( "I'm your lover.. I'm your lover!!" );
	str1.replace_last( TEXT( "lover" ), TEXT( "fucker" ) );

	if( str1 == TEXT( "I'm your lover.. I'm your fucker!!" ) )
	{
		::printf( "test_replace_last() - ok\n" );
	}
}

void test_replace_all()
{
	string str1 = TEXT( "I'm your lover.. I'm your lover!!" );
	str1.replace_all( TEXT( "lover" ), TEXT( "fucker" ) );

	if( str1 == TEXT( "I'm your fucker.. I'm your fucker!!" ) )
	{
		::printf( "test_replace_all() - ok\n" );
	}
}

void test_remvoe()
{
	string str1 = TEXT( "lofuckve" );
	str1.remove( TEXT( "fuck" ) );

	if( str1 == TEXT( "love" ) )
	{
		::printf( "test_remvoe() - ok\n" );
	}
}

void test_parser()
{
	int i = string::parse_int( TEXT( "500" ) );
	float f = string::parse_float( TEXT( "100.5" ) );
	double d = string::parse_double( TEXT( "1.000000001" ) );

	i += 100;
	f += 0.3f;
	d *= 2.0;

	if( i == 600 && f == 100.8f && d == 2.000000002 )
	{
		::printf( "test_parser() - ok\n" );
	}
}

void test_to_upper()
{
	string str1 = TEXT( "hardcoding" );
	str1.to_upper();

	if( str1 == TEXT( "HARDCODING" ) )
	{
		::printf( "test_to_upper() - ok\n" );
	}
}

void test_to_lower()
{
	string str1 = TEXT( "HARDCODING" );
	str1.to_lower();

	if( str1 == TEXT( "hardcoding" ) )
	{
		::printf( "test_to_lower() - ok\n" );
	}
}

void test_push_back()
{
	string str1 = TEXT( "Batma" );
	str1.push_back( TEXT( 'n' ) );

	if( str1 == TEXT( "Batman" ) )
	{
		::printf( "test_push_back() - ok\n" );
	}
}

void test_insert()
{
	string origin_str = TEXT( "Oh" );
	origin_str.insert( 2, 5, TEXT( 'h' ) );

	if( origin_str != TEXT( "Ohhhhhh" ) )
	{
		return;
	}

	origin_str = TEXT( "Batman Knight" );
	string insert_str = TEXT( "Dark" );
	origin_str.insert( 7, insert_str );

	if( origin_str != TEXT( "Batman DarkKnight" ) )
	{
		return;
	}

	origin_str = TEXT( "Oh My " );
	insert_str = TEXT( "GodLike" );
	origin_str.insert( 6, insert_str, 3 );

	if( origin_str != TEXT( "Oh My God" ) )
	{
		return;
	}

	origin_str = TEXT( "Batman Knight" );
	insert_str = TEXT( "Darkness" );
	origin_str.insert( 7, insert_str, 0, 4 );

	if( origin_str != TEXT( "Batman DarkKnight" ) )
	{
		return;
	}

	::printf( "test_insert() - ok\n" );
}

void test_erase()
{
	string str1 = TEXT( "HhhhhardCoding" );
	str1.erase( 1, 4 );

	if( str1 == TEXT( "HardCoding" ) )
	{
		::printf( "test_erase() - ok\n" );
	}
}

void test_start_with()
{
	string str1 = TEXT( "Oh My God" );
	string find_str = TEXT( "Oh" );

	if( str1.start_with( find_str ) )
	{
		::printf( "test_start_with() - ok\n" );
	}
}

void test_end_with()
{
	string str1 = TEXT( "Oh My God" );
	string find_str = TEXT( "God" );

	if( str1.end_with( find_str ) )
	{
		::printf( "test_end_with() - ok\n" );
	}
}

void test_buffer()
{
	string str1 = TEXT( "Batman" );

    if( string_helper<string::char_type>::compare( str1.buffer(), TEXT( "Batman" ) ) == 0 )
	{
		::printf( "test_buffer() - ok\n" );
	}
}

int tmain( int /*argc*/, char* /*argv*/[] )
{
	test_constructor();
	test_is_empty();
	test_length();
	test_resize();
	test_clear();
	test_compare_operators();
	test_plus();
	test_array();
	test_string_format();
	test_trim();
	test_trim_left();
	test_trim_right();
	test_make_upper();
	test_make_lower();
	test_compare_no_case();
	test_compare();
	test_parse_number();
	test_left_right_mid();
	test_sub_string();
	test_find();
	test_reverse_find();
	test_replace_first();
	test_replace_last();
	test_replace_all();
	test_remvoe();
	test_parser();
	test_to_upper();
	test_to_lower();
	test_push_back();
	test_insert();
	test_erase();
	test_start_with();
	test_end_with();
	test_buffer();

	return 0;
}