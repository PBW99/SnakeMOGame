#pragma once
#include "SnakeShared.h"

//#define DEBUGPRINT
#include "DebugPrint.h"
#define FRIEND_DP() friend class DebugPrint;
#ifdef DEBUGPRINT
#define PRINT_OM() DebugPrint::GetIns().PrintOM();
#define PRINT_NetMS() DebugPrint::GetIns().PrintNetMS();
#define DP(...) cout<<__VA_ARGS__ << "\n";
#else
#define PRINT_OM() 
#define PRINT_NetMS() 
#define DP(...)
#endif

#define DEBUGPRINT2
#ifdef DEBUGPRINT2
#define DP2(...) cout<<__VA_ARGS__ << "\n";
#else
#define DP2(...)
#endif


#include "FoodManager.h"
#include "ReplicationManagerServer.h"
#include "ClientProxy.h"
#include "NetworkManagerServer.h"
#include "SnakeServer.h"
#include "FoodServer.h"
#include "Server.h"

