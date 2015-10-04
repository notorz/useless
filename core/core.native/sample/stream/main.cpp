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
#include <vector>

#include "../../source/stream.h"

using namespace useless;

int _tmain( int /*argc*/, _TCHAR* /*argv[]*/ )
{
	filebuf fb( "test.txt", std::ios_base::out );
	
	char* value = "qqqqqaaaaazzzzz";
	fb.write( value, 15 );

	return 0;
}