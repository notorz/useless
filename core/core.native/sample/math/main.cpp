//
// Copyright (c) 2015. Lee eui jong.
//
// Distributed under the MIT License.
//

#include <stdio.h>
#include <tchar.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "core.native/math.h"

using namespace useless;

int _tmain(int /*argc*/, _TCHAR* /*argv[]*/)
{
	std::cout << math::deg_to_rad(180.0) << std::endl;
	std::cout << math::rad_to_deg(math::PI) << std::endl;

	return 0;
}