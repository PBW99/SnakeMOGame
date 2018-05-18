#include "SnakePCH.h"


using namespace std;


void GameObject::SetPos(int x, int y)
{
	this->mPos = std::make_pair(x, y);
}


void GameObject::SetNetworkId(int inNetworkId)
{
	this->mNetworkId = inNetworkId;
}

void GameObject::SetDoesWantToDie(bool tf)
{
	isWantToDead = tf;
}
