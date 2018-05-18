#include "SnakeClientPCH.h"

void SnakeClient::Render()
{
	pair<int, int>* ltVertex = &RenderManager::GetIns().ltVertexPos;
	//	for (const auto& iPos : mTails)
	for (const auto& iPos : mTails)
	{
		Sprite_Draw(iPos.first - ltVertex->first,
		            iPos.second - ltVertex->second,
		            mColor,
		            kTailIcon);
	}
	Sprite_Draw(this->mPos.first - ltVertex->first,
	            this->mPos.second - ltVertex->second,
	            mColor,
	            kHeadIcon);
}

void SnakeClient::HandleDying()
{
	if (this->mPlayerName == g_playerName)
		throw std::runtime_error("Player Die");
}
