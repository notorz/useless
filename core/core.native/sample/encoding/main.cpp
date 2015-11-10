//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#include <stdio.h>

#include "core.native/encoding.h"
#include "core.native/string.h"

using namespace useless;

bool test_static_member()
{
    if( encoding::convert( encoding::get(), encoding::ascii(), "lover_fucker" ).compare( "lover_fucker" ) != 0 )
	{
		return false;
	}
    
    if( encoding::convert( encoding::get(), encoding::utf8(), "lover_fucker" ).compare( "lover_fucker" ) != 0 )
    {
        return false;
    }
    
    if( encoding::convert( encoding::get(), "lover_fucker" ).compare( L"lover_fucker" ) != 0 )
    {
        return false;
    }
    
    if( encoding::convert( encoding::get(), L"lover_fucker" ).compare( "lover_fucker" ) != 0 )
    {
        return false;
    }
    
	return true;
}

bool test_utf8_encoding()
{
	const char temp[ 13 ] = { -20, -109, -72, -21, -86, -88, -20, -105, -122, -21, -118, -108, 0 };
	if( encoding::utf8().from_wide( L"쓸모없는" ).compare( temp ) != 0 )
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
    
    if( encoding::utf8().to_wide( temp ).compare( L"쓸모없는" ) != 0 )
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

bool test_korean_encoding()
{
    const char temp[ 9 ] = { -66, -75, -72, -16, -66, -8, -76, -62, 0 };
    if( encoding::get( charset::korean ).from_wide( L"쓸모없는" ).compare( temp ) != 0 )
	{
		return false;
	}

	if( encoding::get( charset::korean ).from_wide( L"lover" ).compare( "lover" ) != 0 )
	{
		return false;
	}

	if( encoding::get( charset::korean ).from_wide( L"lover" ).compare( "fucker" ) == 0 )
	{
		return false;
	}

	if( encoding::get( charset::korean ).to_wide( temp ).compare( L"쓸모없는" ) != 0 )
	{
		return false;
	}

	if( encoding::get( charset::korean ).to_wide( "lover" ).compare( L"lover" ) != 0 )
	{
		return false;
	}

	if( encoding::get( charset::korean ).to_wide( "lover" ).compare( L"fucker" ) == 0 )
	{
		return false;
	}

	return true;
}

int main()
{
	printf( "test_static_member - %s\n",	test_static_member() ? "ok" : "failed" );
	printf( "test_utf8_encoding - %s\n",	test_utf8_encoding() ? "ok" : "failed" );
	printf( "test_korean_encoding - %s\n",	test_korean_encoding() ? "ok" : "failed" );

	return 0;
}