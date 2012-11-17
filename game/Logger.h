

#pragma once
#include <iostream>
class Logger
{
public:

	static void LogError(std::string msg)
	{
		Filler("[ERROR] " + msg);
	}

	static void LogWarning(std::string msg)
	{
		Filler("[WARNING] " + msg);
	}

	static void LogDebug(std::string msg)
	{
		Filler("[DEBUG] " + msg);
	}

	static void LogInfo(std::string msg)
	{
		Filler("[INFO] " + msg);
	}

	static void Filler(std::string msg)
	{
		std::cout << msg;
		std::cout.flush();

	}
};
