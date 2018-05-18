#pragma once

class DebugPrint
{
private:
	DebugPrint(){};
public:
	static DebugPrint& GetIns()
	{
		static DebugPrint debugPrint;
		return debugPrint;
	}
	void PrintOM();
	void PrintNetMS();
};
