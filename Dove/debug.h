#pragma once
#include <iostream>

#ifdef _DEBUG
#define dout cout
#else
#define dout 0 && cout
#endif
