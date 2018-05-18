#pragma once

//#include "UtilMath.h"


class RenderManager
{
private:
	RenderManager()
	{
	};
public:
	static RenderManager& GetIns()
	{
		static RenderManager mrenderManager;
		return mrenderManager;
	}

	void Update();
	void CalLeftTopVertex();
	void RenderStage(void);
	void RenderStr(std::string& str, int x,int y);
	void RenderStrColor(std::string& str, int x,int y,CONSOLE_COLOR color);
	void RenderPos(void  );
	void RenderLen(void );

	std::pair<int, int> ltVertexPos;
};
