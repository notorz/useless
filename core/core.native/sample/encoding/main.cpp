//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iostream>

#include "core.native/encoding.h"
#include "core.native/string.h"

using namespace useless;

bool test_static_member()
{
	if( encoding::convert( encoding::default(), encoding::get( 20127 ), "lover와fucker" ).compare( "lover?fucker" ) != 0 )
	{
		return false;
	}

	if( encoding::convert( encoding::default(), encoding::get( 20127 ), "lover와fucker" ).compare( "lover와fucker" ) == 0 )
	{
		return false;
	}

	return true;
}

bool test_utf8_encoding()
{
	const char check[ 13 ] = { -20, -109, -72, -21, -86, -88, -20, -105, -122, -21, -118, -108, 0 };
	if( encoding::utf8().from_wide( L"쓸모없는" ).compare( check ) != 0 )
	{
		return false;
	}

	if( encoding::utf8().from_wide( L"lover" ).compare( "lover" ) != 0 )
	{
		return false;
	}

	if( encoding::utf8().from_wide( L"lover" ).compare( "fucker" ) == 0 )
	{
		return false;
	}

	const wchar_t checkW[ 8 ] = { 65533, 65533, 65533, 65533, 65533, 65533, 65533, 0 };
	if( encoding::utf8().to_wide( "쓸모없는" ).compare( checkW ) != 0 )
	{
		return false;
	}

	if( encoding::utf8().to_wide( "lover" ).compare( L"lover" ) != 0 )
	{
		return false;
	}

	if( encoding::utf8().to_wide( "lover" ).compare( L"fucker" ) == 0 )
	{
		return false;
	}

	return true;
}

bool test_codepage949_encoding()
{
	if( encoding::get( 949 ).from_wide( L"쓸모없는" ).compare( "쓸모없는" ) != 0 )
	{
		return false;
	}

	if( encoding::get( 949 ).from_wide( L"lover" ).compare( "lover" ) != 0 )
	{
		return false;
	}

	if( encoding::get( 949 ).from_wide( L"lover" ).compare( "fucker" ) == 0 )
	{
		return false;
	}

	if( encoding::get( 949 ).to_wide( "쓸모없는" ).compare( L"쓸모없는" ) != 0 )
	{
		return false;
	}

	if( encoding::get( 949 ).to_wide( "lover" ).compare( L"lover" ) != 0 )
	{
		return false;
	}

	if( encoding::get( 949 ).to_wide( "lover" ).compare( L"fucker" ) == 0 )
	{
		return false;
	}

	return true;
}

int main()
{
	printf( "test_static_member - %s\n",			test_static_member() ? "ok" : "failed" );
	printf( "test_utf8_encoding - %s\n",			test_utf8_encoding() ? "ok" : "failed" );
	printf( "test_codepage949_encoding - %s\n",	test_codepage949_encoding() ? "ok" : "failed" );

	return 0;
}