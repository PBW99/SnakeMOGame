#include "SnakeServerPCH.h"

namespace
{
	const float kRespawnDelay = 3.f;
}

ClientProxy::ClientProxy( const SocketAddress& inSocketAddress, const string& inName, int inPlayerId ) :
mSocketAddress( inSocketAddress ),
mName( inName ),
mPlayerId( inPlayerId ),
mIsLastMoveTimestampDirty( false ),
mTimeToRespawn( 0.f )
{
	UpdateLastPacketTime();
}


void ClientProxy::UpdateLastPacketTime()
{
	mLastPacketFromClientTime = Timing::sInstance.GetTimef(); 
}
