#pragma once

class Context
{
private:
	Context()
	{
		ObjectManager::GetIns();
		World::GetIns();
		ScoreBoardManager::StaticInit();
	};
public:
	static Context& GetIns()
	{
		static Context ctx;
		return ctx;
	}
};

template <typename Enumeration>
auto as_integer(Enumeration const value)
-> typename std::underlying_type<Enumeration>::type
{
	return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}
