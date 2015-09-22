//
// Copyright (c) 2015. notorz.
//
// Distributed under the MIT License.
//

#include <stdio.h>
#include <tchar.h>
#include <memory.h>
#include <map>

#include "../../source/string.h"

using namespace useless;

void test_constructor()
{
	string str1( L'a' );
	string str2( L"Test String" );
	string str3( L"Test", 3 );
	string str4( str3 );

	if( str1 == L'a' && 
		str2 == L"Test String" && 
		str3 == L"Tes" && 
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
		str = L"abc";

		if( !str.is_empty() )
		{
			::printf( "test_is_empty() - ok\n" );
		}
	}
}

void test_length()
{
	string str = L"0123456789";

	if( str.length() == 10 )
	{
		str = L"abcd";

		if( str.length() == 4 )
		{
			::printf( "test_length() - ok\n" );
		}
	}
}

void test_resize()
{
	string str = L"0123456789";

	str.resize( str.length() + 2, '!' );

	if( str == L"0123456789!!" && str.length() == 12 )
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
	string str = L"0123456789";

	str.clear();

	if( str.is_empty() )
	{
		::printf( "test_clear() - ok\n" );
	}
}

void test_compare_operators()
{
	string str1( L"hello" );
	string str2( L"world!!" );
	string str3( L"hello" );

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
	test_map.insert( std::pair<string, int>( L"one", 1 ) );
	test_map.insert( std::pair<string, int>( L"four", 4 ) );
	test_map.insert( std::pair<string, int>( L"two", 2 ) );
	test_map.insert( std::pair<string, int>( L"ten", 10 ) );
	test_map.insert( std::pair<string, int>( L"six", 6 ) );

	std::map<string, int>::iterator find_data1 = test_map.find( L"one" );
	std::map<string, int>::iterator find_data2 = test_map.find( L"two" );
	std::map<string, int>::iterator find_data3 = test_map.find( L"four" );
	std::map<string, int>::iterator find_data4 = test_map.find( L"six" );
	std::map<string, int>::iterator find_data5 = test_map.find( L"ten" );

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
	string str1 = L"one";
	string str2 = L"two";
	string str3 = L"three";

	if( str1 + str2 + str3 != L"onetwothree" )
	{
		return;
	}

	string str0 = str1 + str3;
	if( str0 != L"onethree" )
	{
		return;
	}

	str0 += str2;
	if( str0 != L"onethreetwo" )
	{
		return;
	}

	::printf( "test_plus() - ok\n" );
}

void test_array()
{
	string str = L"abcdefghigklmonop";

	if( str[ 2 ] == L'c' )
	{
		::printf( "test_array() - ok\n" );
	}
}

void test_string_format()
{
	string str = string::make_format( L"%d+%d=%d", 1, 2, 1 + 2 );
	if( str != L"1+2=3" )
	{
		return;
	}

	str.format( L"%d-%d=%d", 1, 2, 1 - 2 );
	if( str != L"1-2=-1" )
	{
		return;
	}

	::printf( "test_string_format() - ok\n" );
}

void test_trim()
{
	string str1 = L"\t\tabc\v\n";
	str1.trim();
	if( str1 != L"abc" )
	{
		return;
	}

	str1 = L"\t  string trim test       \t";
	str1.trim();
	if( str1 != L"string trim test" )
	{
		return;
	}

	::printf( "test_trim() - ok\n" );
}

void test_trim_left()
{
	string str1 = L"  \t \t  \t  abc";
	string str2 = L"abc \t  \t  \t   ";

	str1.trim_left();
	str2.trim_left();

	if( str1 == L"abc" && str2 != L"abc" )
	{
		::printf( "test_trim_left() - ok\n" );
	}
}

void test_trim_right()
{
	string str1 = L"  \t \t  \t  abc";
	string str2 = L" abc \t  \t  \t   ";

	str1.trim_right();
	str2.trim_right();

	if( str1 != L"abc" && str2 == L" abc" )
	{
		::printf( "test_trim_right() - ok\n" );
	}
}

void test_make_upper()
{
	string str1 = L"aBc#Def/GhI-";
	string str2 = str1.make_upper();
	if( str2 == L"ABC#DEF/GHI-" )
	{
		::printf( "test_make_upper() - ok\n" );
	}
}

void test_make_lower()
{
	string str1 = L"aBC/dEf#ghI-";
	string str2 = str1.make_lower();
	if( str2 == L"abc/def#ghi-" )
	{
		::printf( "test_make_lower() - ok\n" );
	}
}

void test_compare_no_case()
{
	string str1 = L"ABCDEFG";
	string str2 = L"abcdefg";

	if( str1.compare_no_case( str2 ) == 0 )
	{
		::printf( "test_compare_no_case() - ok\n" );
	}
}

void test_compare()
{
	string str1 = L"123";
	string str2 = L"456";
	string str3 = L"123456";

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
	string str1 = L"12345";
	string str2 = L"12345.9";
	string str3 = L"12345.99";

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
	string str = L"0123456789";
	string str_left4 = str.left( 4 );
	string str_right4 = str.right( 4 );
	string str_mid4to6 = str.mid( 4, 3 );

	if( str_left4 == L"0123" && str_right4 == L"6789" && str_mid4to6 == L"456" )
	{
		::printf( "test_left_right_mid() - ok\n" );
	}
}

void test_sub_string()
{
	string str1 = L"0123456789";
	string str2 = str1.sub_string( 4, 3 );
	string str3 = str1.sub_string( 6 );

	if( str2 == L"456" && str3 == L"6789" )
	{
		::printf( "test_sub_string() - ok\n" );
	}
}

void test_find()
{
	string str1 = L"01234567890123456789";
	size_t find_index1 = str1.find( L"456" );
	size_t find_index2 = str1.find( L"456", 6 );

	if( find_index1 != 4 || find_index2 != 14 )
	{
		return;
	}

	string find_str = L"456";
	find_index1 = str1.find( find_str );
	find_index2 = str1.find( find_str, 6 );

	if( find_index1 != 4 || find_index2 != 14 )
	{
		return;
	}

	find_index1 = str1.find( L'3' );
	find_index2 = str1.find( L'3', 5 );

	if( find_index1 != 3 || find_index2 != 13 )
	{
		return;
	}

	str1 = L"This is a sample string for this program";
	find_str = L"for";
	find_index1 = str1.find( find_str, 10, 2 );

	if( find_index1 != 24 )
	{
		return;
	}

	find_index1 = str1.find( L"useless" );
	if( find_index1 != string::npos() )
	{
		return;
	}

	::printf( "test_find() - ok\n" );
}

void test_reverse_find()
{
	string str1 = L"01234567890123456789";
	size_t find_index1 = str1.reverse_find( L"456" );
	size_t find_index2 = str1.reverse_find( L"456", 6 );

	if( find_index1 != 14 || find_index2 != 4 )
	{
		return;
	}

	string find_str = L"456";
	find_index1 = str1.reverse_find( find_str );
	find_index2 = str1.reverse_find( find_str, 6 );

	if( find_index1 != 14 || find_index2 != 4 )
	{
		return;
	}

	find_index1 = str1.reverse_find( L'3' );
	find_index2 = str1.reverse_find( L'3', 12 );

	if( find_index1 != 13 || find_index2 != 3 )
	{
		return;
	}

	str1 = L"It is a nice day. I am happy";
	find_str = L"am";
	find_index1 = str1.reverse_find( find_str, 33, 2 );

	if( find_index1 != 20 )
	{
		return;
	}

	find_str = L"useless";
	find_index1 = str1.reverse_find( find_str );

	if( find_index1 != string::npos() )
	{
		return;
	}

	::printf( "test_reverse_find() - ok\n" );
}

void test_replace_first()
{
	string str1 = L"I'm your lover.. I'm your lover!!";
	str1.replace_first( L"lover", L"fucker" );

	if( str1 == L"I'm your fucker.. I'm your lover!!" )
	{
		::printf( "test_replace_first() - ok\n" );
	}
}

void test_replace_last()
{
	string str1 = L"I'm your lover.. I'm your lover!!";
	str1.replace_last( L"lover", L"fucker" );

	if( str1 == L"I'm your lover.. I'm your fucker!!" )
	{
		::printf( "test_replace_last() - ok\n" );
	}
}

void test_replace_all()
{
	string str1 = L"I'm your lover.. I'm your lover!!";
	str1.replace_all( L"lover", L"fucker" );

	if( str1 == L"I'm your fucker.. I'm your fucker!!" )
	{
		::printf( "test_replace_all() - ok\n" );
	}
}

void test_remvoe()
{
	string str1 = L"lofuckve";
	str1.remove( L"fuck" );

	if( str1 == L"love" )
	{
		::printf( "test_remvoe() - ok\n" );
	}
}

void test_parser()
{
	int i = string::parse_int( L"500" );
	float f = string::parse_float( L"100.5" );
	double d = string::parse_double( L"1.000000001" );

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
	string str1 = L"hardcoding";
	str1.to_upper();

	if( str1 == L"HARDCODING" )
	{
		::printf( "test_to_upper() - ok\n" );
	}
}

void test_to_lower()
{
	string str1 = L"HARDCODING";
	str1.to_lower();

	if( str1 == L"hardcoding" )
	{
		::printf( "test_to_lower() - ok\n" );
	}
}

void test_push_back()
{
	string str1 = L"Batma";
	str1.push_back( 'n' );

	if( str1 == L"Batman" )
	{
		::printf( "test_push_back() - ok\n" );
	}
}

void test_insert()
{
	string origin_str = L"Oh";
	origin_str.insert( 2, 5, 'h' );

	if( origin_str != L"Ohhhhhh" )
	{
		return;
	}

	origin_str = L"Batman Knight";
	string insert_str = L"Dark";
	origin_str.insert( 7, insert_str );

	if( origin_str != L"Batman DarkKnight" )
	{
		return;
	}

	origin_str = L"Oh My ";
	insert_str = L"GodLike";
	origin_str.insert( 6, insert_str, 3 );

	if( origin_str != L"Oh My God" )
	{
		return;
	}

	origin_str = L"Batman Knight";
	insert_str = L"Darkness";
	origin_str.insert( 7, insert_str, 0, 4 );

	if( origin_str != L"Batman DarkKnight" )
	{
		return;
	}

	::printf( "test_insert() - ok\n" );
}

void test_erase()
{
	string str1 = L"HhhhhardCoding";
	str1.erase( 1, 4 );

	if( str1 == L"HardCoding" )
	{
		::printf( "test_erase() - ok\n" );
	}
}

void test_start_with()
{
	string str1 = L"Oh My God";
	string find_str = L"Oh";

	if( str1.start_with( find_str ) )
	{
		::printf( "test_start_with() - ok\n" );
	}
}

void test_end_with()
{
	string str1 = L"Oh My God";
	string find_str = L"God";

	if( str1.end_with( find_str ) )
	{
		::printf( "test_end_with() - ok\n" );
	}
}

void test_buffer()
{
	string str1 = L"Batman";

	if( string_helper<wchar_t>::compare( str1.buffer(), L"Batman" ) == 0 )
	{
		::printf( "test_buffer() - ok\n" );
	}
}

int _tmain( int /*argc*/, _TCHAR* /*argv[]*/ )
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