#pragma once
#include <iostream>

#ifdef _DEBUG
#define dout std::cout
#else
#define dout 0 && std::cout
#endif
