#pragma once
#include "SnakeShared.h"
//#define DEBUGPRINT
#ifdef DEBUGPRINT
#define DP(...) cout<<__VA_ARGS__ << "\n";
#else
#define DP(...)
#endif
#include <cassert>
#include <map>
#include <exception>

using std::multimap;

#include "RenderManager.h"
#include "InputManager.h"
#include "FoodClient.h"
#include "SnakeClient.h"
#include "ReplicationManagerClient.h"
#include "NetworkManagerClient.h"
#include "Client.h"

extern string g_destSocketStr;
extern string g_playerName;