#define _CRT_SECURE_NO_WARNINGS

#include "Logger.h"
#include <Windows.h>

namespace arc
{
	LogManager& LogManager::Instance()
	{
		static LogManager sInstance;
		return sInstance;
	}

	/////////////////////////////////////////////////////////

	ConsoleLogger::ConsoleLogger()
	{
		AllocConsole();
		freopen("conin$" , "r", stdin);
		freopen("conout$", "w", stdout);
		freopen("conout$", "w", stderr);
	}

	void ConsoleLogger::Log(const std::string& str)
	{
		printf("%s\n", str.c_str());
	}
	
	/////////////////////////////////////////////////////////
}