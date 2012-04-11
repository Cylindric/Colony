#pragma once

#ifdef DEBUG
#define _CRTDBG_MAP_ALLOC
//#include <vld.h>
#define DEBUG_OUT(t) std::cout << t << std::endl
#endif

//////////////
// INCLUDES //
//////////////
#include <iostream>


using std::cerr;
using std::cout;
using std::endl;
