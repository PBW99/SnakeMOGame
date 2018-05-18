#pragma once
#include "SnakeShared.h"
//#define DEBUGPRINT
#ifdef DEBUGPRINT
#define DP(...) cout<<__VA_ARGS__ << "\n";
#else
#define DP(...)
#endif
