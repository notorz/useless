//
// Copyright (c) 2015. SeongJun Park.
//
// Distributed under the MIT License.
//

#include <stdio.h>
#include <tchar.h>
#include <fstream>
#include <sstream>
#include <iostream>
#pragma warning( disable : 4100 )
#include <boost/thread.hpp>
#pragma warning( default : 4100 )
#include <boost/locale.hpp>

#include "core.native/encoding.h"
#include "core.native/string.h"

using namespace useless;

int _tmain( int /*argc*/, _TCHAR* /*argv[]*/ )
{
	//std::string utf8_string = boost::locale::conv::to_utf<char>( "硬いしじ", "Latin1" );
	//printf( "%s\n", utf8_string.c_str() );
	//std::locale::global( std::locale( "en_US.UTF8" ) );
	//std::locale::global()
	//boost::locale::generator gen;
	//std::locale loc = gen( "" );
	//std::locale loc = std::locale( "ko_KR.UTF-8" );
	//const char* loc_name = loc.name().c_str();
	//::printf( "%s\n", loc_name );
	
	//const encoding& e = encoding::unicode();
	//const char* e_name = e.name();
	//const encoding& e2 = encoding::ascii();
	//const char* e2_name = e2.name();
	//const encoding& e3 = encoding::default();
	//const char* e3_name = e3.name();
	//const encoding& e = encoding::get( "ko-kr" );
	//const char* e_name = e.name();
	//string_ansi val = e.from_wide( L"生馬馬" );
	//::printf( "%s\n%s\n", val.buffer(), e_name );
	//::printf( "%s\n", e2_name );
	//::printf( "%s\n", e3_name );
	//::printf( "%s\n", e_name );

	//std::locale l = std::locale( "euc-kr" );
	//std::locale loc1;
	//std::string loc1name = loc1.name();

	//boost::locale::generator gen;
	//std::locale loc2 = gen( "" );
	//std::string loc2name = loc2.name();

	//std::locale::global( loc1 );
	//std::locale::global( loc2 );


	return 0;
}