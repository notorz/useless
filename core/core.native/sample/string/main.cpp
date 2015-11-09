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

using namespace useless;

bool test_constructor()
{
	string str1( TEXT( 'a' ) );
	string str2( TEXT( "Test String" ) );
	string str3( TEXT( "Test" ), 3 );
	string str4( str3 );

	if( str1 != TEXT( 'a' ) ||
		str2 != TEXT( "Test String" ) ||
		str3 != TEXT( "Tes" ) ||
		str3.length() != 3 ||
		str4 != str3 )
	{
		return false;
	}

	return true;
}

bool test_is_empty()
{
	string str;

	if( str.is_empty() )
	{
		str = TEXT( "abc" );

		if( str.is_empty() )
		{
			return false;
		}
	}

	return true;
}

bool test_length()
{
	string str = TEXT( "0123456789" );

	if( str.length() == 10 )
	{
		str = TEXT( "abcd" );

		if( str.length() != 4 )
		{
			return false;
		}
	}

	return true;
}

bool test_resize()
{
	string str = TEXT( "0123456789" );

	str.resize( str.length() + 2, '!' );

	if( str == TEXT( "0123456789!!" ) && str.length() == 12 )
	{
		str.resize( 25 );

		if( str.length() != 25 )
		{
			return false;
		}
	}

	return true;
}

bool test_clear()
{
	string str = TEXT( "0123456789" );

	str.clear();

	if( !str.is_empty() )
	{
		return false;
	}

	return true;
}

bool test_compare_operators()
{
	string str1( TEXT( "hello" ) );
	string str2( TEXT( "world!!" ) );
	string str3( TEXT( "hello" ) );

	if( str1 != str3 ||
		str1 == str2 ||
		str1 >= str2 ||
		str2 <= str1 ||
		str1 < str3 ||
		str3 > str1 ||
		str1 > str2 ||
		str2 < str1 )
	{
		return false;
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

	if( find_data1 == test_map.end() || 
		find_data2 == test_map.end() ||
		find_data3 == test_map.end() ||
		find_data4 == test_map.end() ||
		find_data5 == test_map.end() )
	{
		if( find_data1->second != 1 ||
			find_data2->second != 2 ||
			find_data3->second != 4 ||
			find_data4->second != 6 ||
			find_data5->second != 10 )
		{
			return false;
		}
	}

	return true;
}

bool test_plus()
{
	string str1 = TEXT( "one" );
	string str2 = TEXT( "two" );
	string str3 = TEXT( "three" );

	if( str1 + str2 + str3 != TEXT( "onetwothree" ) )
	{
		return false;
	}

	string str0 = str1 + str3;
	if( str0 != TEXT( "onethree" ) )
	{
		return false;
	}

	str0 += str2;
	if( str0 != TEXT( "onethreetwo" ) )
	{
		return false;
	}

	return true;
}

bool test_array()
{
	string str = TEXT( "abcdefghigklmonop" );

	if( str[ 2 ] != TEXT( 'c' ) )
	{
		return false;
	}

	return true;
}

bool test_string_format()
{
	string str = string::make_format( TEXT( "%d+%d=%d, %d+%d=%d" ), 1, 2, 1 + 2, 4, 5, 4 + 5 );
	if( str != TEXT( "1+2=3, 4+5=9" ) )
	{
		return false;
	}

	str.format( TEXT( "%d-%d=%d" ), 1, 2, 1 - 2 );
	if( str != TEXT( "1-2=-1" ) )
	{
		return false;
	}

	return true;
}

bool test_trim()
{
	string str1 = TEXT( "\t\tabc\v\n" );
	str1.trim();
	if( str1 != TEXT( "abc" ) )
	{
		return false;
	}

	str1 = TEXT( "\t  string trim test       \t" );
	str1.trim();
	if( str1 != TEXT( "string trim test" ) )
	{
		return false;
	}

	return true;
}

bool test_trim_left()
{
	string str1 = TEXT( "  \t \t  \t  abc" );
	string str2 = TEXT( "abc \t  \t  \t   " );

	str1.trim_left();
	str2.trim_left();

	if( str1 != TEXT( "abc" ) || str2 == TEXT( "abc" ) )
	{
		return false;
	}

	return true;
}

bool test_trim_right()
{
	string str1 = TEXT( "  \t \t  \t  abc" );
	string str2 = TEXT( " abc \t  \t  \t   " );

	str1.trim_right();
	str2.trim_right();

	if( str1 == TEXT( "abc" ) || str2 != TEXT( " abc" ) )
	{
		return false;
	}

	return true;
}

bool test_make_upper()
{
	string str1 = TEXT( "aBc#Def/GhI-" );
	string str2 = str1.make_upper();
	if( str2 != TEXT( "ABC#DEF/GHI-" ) )
	{
		return false;
	}

	return true;
}

bool test_make_lower()
{
	string str1 = TEXT( "aBC/dEf#ghI-" );
	string str2 = str1.make_lower();
	if( str2 != TEXT( "abc/def#ghi-" ) )
	{
		return false;
	}

	return true;
}

bool test_compare_no_case()
{
	string str1 = TEXT( "ABCDEFG" );
	string str2 = TEXT( "abcdefg" );

	if( str1.compare_no_case( str2 ) != 0 )
	{
		return false;
	}

	return true;
}

bool test_compare()
{
	string str1 = TEXT( "123" );
	string str2 = TEXT( "456" );
	string str3 = TEXT( "123456" );

	if( str3.compare( str1 + str2 ) != 0 || str1.compare( str2 ) == 0 )
	{
		return false;
	}

	if( str3.compare( 3, 3, str2 ) != 0 || str3.compare( 3, 2, str2, 2 ) != 0 )
	{
		return false;
	}

	if( str2.compare( 0, 3, str3, 3, 3 ) != 0 )
	{
		return false;
	}

	return true;
}

bool test_parse_number()
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

	if( str2int != 12346 ||
		str2float != 12346.0f ||
		str2double != 12345.99001 )
	{
		return false;
	}

	return true;
}

bool test_left_right_mid()
{
	string str = TEXT( "0123456789" );
	string str_left4 = str.left( 4 );
	string str_right4 = str.right( 4 );
	string str_mid4to6 = str.mid( 4, 3 );

	if( str_left4 != TEXT( "0123" ) || str_right4 != TEXT( "6789" ) || str_mid4to6 != TEXT( "456" ) )
	{
		return false;
	}

	return true;
}

bool test_sub_string()
{
	string str1 = TEXT( "0123456789" );
	string str2 = str1.sub_string( 4, 3 );
	string str3 = str1.sub_string( 6 );

	if( str2 != TEXT( "456" ) || str3 != TEXT( "6789" ) )
	{
		return false;
	}

	return true;
}

bool test_find()
{
	string str1 = TEXT( "01234567890123456789" );
	size_t find_index1 = str1.find( TEXT( "456" ) );
	size_t find_index2 = str1.find( TEXT( "456" ), 6 );

	if( find_index1 != 4 || find_index2 != 14 )
	{
		return false;
	}

	string find_str = TEXT( "456" );
	find_index1 = str1.find( find_str );
	find_index2 = str1.find( find_str, 6 );

	if( find_index1 != 4 || find_index2 != 14 )
	{
		return false;
	}

	find_index1 = str1.find( TEXT( '3' ) );
	find_index2 = str1.find( TEXT( '3' ), 5 );

	if( find_index1 != 3 || find_index2 != 13 )
	{
		return false;
	}

	str1 = TEXT( "This is a sample string for this program" );
	find_str = TEXT( "for" );
	find_index1 = str1.find( find_str, 10, 2 );

	if( find_index1 != 24 )
	{
		return false;
	}

	find_index1 = str1.find( TEXT( "useless" ) );
	if( find_index1 != string::npos() )
	{
		return false;
	}

	return true;
}

bool test_reverse_find()
{
	string str1 = TEXT( "01234567890123456789" );
	size_t find_index1 = str1.reverse_find( TEXT( "456" ) );
	size_t find_index2 = str1.reverse_find( TEXT( "456" ), 6 );

	if( find_index1 != 14 || find_index2 != 4 )
	{
		return false;
	}

	string find_str = TEXT( "456" );
	find_index1 = str1.reverse_find( find_str );
	find_index2 = str1.reverse_find( find_str, 6 );

	if( find_index1 != 14 || find_index2 != 4 )
	{
		return false;
	}

	find_index1 = str1.reverse_find( TEXT( '3' ) );
	find_index2 = str1.reverse_find( TEXT( '3' ), 12 );

	if( find_index1 != 13 || find_index2 != 3 )
	{
		return false;
	}

	str1 = TEXT( "It is a nice day. I am happy" );
	find_str = TEXT( "am" );
	find_index1 = str1.reverse_find( find_str, 33, 2 );

	if( find_index1 != 20 )
	{
		return false;
	}

	find_str = TEXT( "useless" );
	find_index1 = str1.reverse_find( find_str );

	if( find_index1 != string::npos() )
	{
		return false;
	}

	return true;
}

bool test_replace_first()
{
	string str1 = TEXT( "I'm your lover.. I'm your lover!!" );
	str1.replace_first( TEXT( "lover" ), TEXT( "fucker" ) );

	if( str1 != TEXT( "I'm your fucker.. I'm your lover!!" ) )
	{
		return false;
	}

	return true;
}

bool test_replace_last()
{
	string str1 = TEXT( "I'm your lover.. I'm your lover!!" );
	str1.replace_last( TEXT( "lover" ), TEXT( "fucker" ) );

	if( str1 != TEXT( "I'm your lover.. I'm your fucker!!" ) )
	{
		return false;
	}

	return true;
}

bool test_replace_all()
{
	string str1 = TEXT( "I'm your lover.. I'm your lover!!" );
	str1.replace_all( TEXT( "lover" ), TEXT( "fucker" ) );

	if( str1 != TEXT( "I'm your fucker.. I'm your fucker!!" ) )
	{
		return false;
	}

	return true;
}

bool test_remvoe()
{
	string str1 = TEXT( "lofuckve" );
	str1.remove( TEXT( "fuck" ) );

	if( str1 != TEXT( "love" ) )
	{
		return false;
	}

	return true;
}

bool test_parser()
{
	int i = string::parse_int( TEXT( "500" ) );
	float f = string::parse_float( TEXT( "100.5" ) );
	double d = string::parse_double( TEXT( "1.000000001" ) );

	i += 100;
	f += 0.3f;
	d *= 2.0;

	if( i != 600 || f != 100.8f || d != 2.000000002 )
	{
		return false;
	}

	return true;
}

bool test_to_upper()
{
	string str1 = TEXT( "hardcoding" );
	str1.to_upper();

	if( str1 != TEXT( "HARDCODING" ) )
	{
		return false;
	}

	return true;
}

bool test_to_lower()
{
	string str1 = TEXT( "HARDCODING" );
	str1.to_lower();

	if( str1 != TEXT( "hardcoding" ) )
	{
		return false;
	}

	return true;
}

bool test_push_back()
{
	string str1 = TEXT( "Batma" );
	str1.push_back( TEXT( 'n' ) );

	if( str1 != TEXT( "Batman" ) )
	{
		return false;
	}

	return true;
}

bool test_insert()
{
	string origin_str = TEXT( "Oh" );
	origin_str.insert( 2, 5, TEXT( 'h' ) );

	if( origin_str != TEXT( "Ohhhhhh" ) )
	{
		return false;
	}

	origin_str = TEXT( "Batman Knight" );
	string insert_str = TEXT( "Dark" );
	origin_str.insert( 7, insert_str );

	if( origin_str != TEXT( "Batman DarkKnight" ) )
	{
		return false;
	}

	origin_str = TEXT( "Oh My " );
	insert_str = TEXT( "GodLike" );
	origin_str.insert( 6, insert_str, 3 );

	if( origin_str != TEXT( "Oh My God" ) )
	{
		return false;
	}

	origin_str = TEXT( "Batman Knight" );
	insert_str = TEXT( "Darkness" );
	origin_str.insert( 7, insert_str, 0, 4 );

	if( origin_str != TEXT( "Batman DarkKnight" ) )
	{
		return false;
	}

	return true;
}

bool test_erase()
{
	string str1 = TEXT( "HhhhhardCoding" );
	str1.erase( 1, 4 );

	if( str1 != TEXT( "HardCoding" ) )
	{
		return false;
	}

	return true;
}

bool test_start_with()
{
	string str1 = TEXT( "Oh My God" );
	string find_str = TEXT( "Oh" );

	if( !str1.start_with( find_str ) )
	{
		return false;
	}

	return true;
}

bool test_end_with()
{
	string str1 = TEXT( "Oh My God" );
	string find_str = TEXT( "God" );

	if( !str1.end_with( find_str ) )
	{
		return false;
	}

	return true;
}

bool test_buffer()
{
	string str1 = TEXT( "Batman" );

    if( string_helper<string::char_type>::compare( str1.buffer(), TEXT( "Batman" ) ) != 0 )
	{
		return false;
	}

	return true;
}

int main()
{
	printf( "test_is_empty - %s\n",				test_is_empty() ? "ok" : "failed" );
	printf( "test_length - %s\n",				test_length() ? "ok" : "failed" );
	printf( "test_resize - %s\n",				test_resize() ? "ok" : "failed" );
	printf( "test_clear - %s\n",					test_clear() ? "ok" : "failed" );
	printf( "test_compare_operators - %s\n",		test_compare_operators() ? "ok" : "failed" );
	printf( "test_plus - %s\n",					test_plus() ? "ok" : "failed" );
	printf( "test_array - %s\n",					test_array() ? "ok" : "failed" );
	printf( "test_string_format - %s\n",			test_string_format() ? "ok" : "failed" );
	printf( "test_trim - %s\n",					test_trim() ? "ok" : "failed" );
	printf( "test_trim_left - %s\n",				test_trim_left() ? "ok" : "failed" );
	printf( "test_trim_right - %s\n",			test_trim_right() ? "ok" : "failed" );
	printf( "test_make_upper - %s\n",			test_make_upper() ? "ok" : "failed" );
	printf( "test_make_lower - %s\n",			test_make_lower() ? "ok" : "failed" );
	printf( "test_compare_no_case - %s\n",		test_compare_no_case() ? "ok" : "failed" );
	printf( "test_compare - %s\n",				test_compare() ? "ok" : "failed" );
	printf( "test_parse_number - %s\n",			test_parse_number() ? "ok" : "failed" );
	printf( "test_left_right_mid - %s\n",		test_left_right_mid() ? "ok" : "failed" );
	printf( "test_sub_string - %s\n",			test_sub_string() ? "ok" : "failed" );
	printf( "test_find - %s\n",					test_find() ? "ok" : "failed" );
	printf( "test_reverse_find - %s\n",			test_reverse_find() ? "ok" : "failed" );
	printf( "test_replace_first - %s\n",			test_replace_first() ? "ok" : "failed" );
	printf( "test_replace_last - %s\n",			test_replace_last() ? "ok" : "failed" );
	printf( "test_replace_all - %s\n",			test_replace_all() ? "ok" : "failed" );
	printf( "test_remvoe - %s\n",				test_remvoe() ? "ok" : "failed" );
	printf( "test_parser - %s\n",				test_parser() ? "ok" : "failed" );
	printf( "test_to_upper - %s\n",				test_to_upper() ? "ok" : "failed" );
	printf( "test_to_lower - %s\n",				test_to_lower() ? "ok" : "failed" );
	printf( "test_push_back - %s\n",				test_push_back() ? "ok" : "failed" );
	printf( "test_insert - %s\n",				test_insert() ? "ok" : "failed" );
	printf( "test_erase - %s\n",					test_erase() ? "ok" : "failed" );
	printf( "test_start_with - %s\n",			test_start_with() ? "ok" : "failed" );
	printf( "test_end_with - %s\n",				test_end_with() ? "ok" : "failed" );
	printf( "test_buffer - %s\n",				test_buffer() ? "ok" : "failed" );

	return 0;
}