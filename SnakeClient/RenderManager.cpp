#include "SnakeClientPCH.h"
#include <functional>

using namespace std;

void RenderManager::Update()
{
	// 스크린 버퍼를 지움
	Buffer_Clear();

	CalLeftTopVertex();
	RenderStage();
	RenderPos();
	RenderLen();

	// 스크린 버퍼를 화면으로 출력
	Buffer_Flip();
}

void RenderManager::CalLeftTopVertex()
{
	ltVertexPos.first =
		max(World::GetIns().mPlayer->mPos.first - dfSCREEN_WIDTH / 2, 0);
	ltVertexPos.second = max(World::GetIns().mPlayer->mPos.second - dfSCREEN_HEIGHT
							 / 2,
							 0);
}

void RenderManager::RenderStage(void)
{
	// 스크린 버퍼에 스프라이트 출력

	// Print Objects
	for (const auto& gameObject : ObjectManager::GetIns().mGameObjects)
	{
		gameObject->Render();
	}
}

void RenderManager::RenderStr(std::string& str, int x, int y)
{
	uint32_t a;

	for (a = 0; a < str.size(); a++)
	{
		Sprite_Extra_Draw(a + x, y, str[a]);
	}
}

void RenderManager::RenderStrColor(std::string&  str,
								   int           x,
								   int           y,
								   CONSOLE_COLOR color)
{
	uint32_t a;
	for (a = 0; a < str.size(); a++)
	{
		Sprite_Extra_Draw(a + x, y, color, str[a]);
	}
}


void RenderManager::RenderPos()
{
	string xPos = to_string(World::GetIns().mPlayer->mPos.first);
	string yPos = to_string(World::GetIns().mPlayer->mPos.second);
	string render;

	render += "POS:x" + xPos + "y" + yPos;

	RenderStr(render, 80, 0);
}

void RenderManager::RenderLen()
{
	ScoreBoardManager::Entry*                          entry;
	int                                                cnt  = 3;
	string                                             rank = "Rank___";
	multimap<unsigned, Snake*, std::greater<unsigned>> entries;

	RenderStr(rank, 80, 2);

	for (const auto& go : ObjectManager::GetIns().mGameObjects)
	{
		Snake* snake = go->GetAsSnake();
		if (snake)
		{
			entries.insert(make_pair(snake->mTails.size(), snake));
		}
	}
	for (const auto& iter : entries)
	{
		Snake* snake = iter.second;
		entry        = ScoreBoardManager::sInstance->GetEntry(snake->mPlayerID);
		string len   = to_string(snake->mTails.size());
		string render;

		render += snake->mPlayerName.substr(0, 4) + "??:" + len;
		RenderStrColor(render, 80, cnt, entry->GetColor());
		cnt++;
		if (cnt > 3 + 10)break;
	}
}
