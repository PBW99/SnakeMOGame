#include "SnakeClientPCH.h"

void FoodClient::Render()
{
	std::pair<int, int>* ltVertex = &RenderManager::GetIns().ltVertexPos;
	Sprite_Draw(this->mPos.first - ltVertex->first, this->mPos.second - ltVertex->second, kIcon);
}