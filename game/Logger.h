

#pragma once
#include <iostream>
class Logger
{
public:

	static void LogError(std::string msg)
	{
		Filler("[ERROR] " + msg + "\n");
	}

	static void LogWarning(std::string msg)
	{
		Filler("[WARNING] " + msg + "\n");
	}

	static void LogDebug(std::string msg)
	{
		Filler("[DEBUG] " + msg + "\n");
	}

	static void LogInfo(std::string msg)
	{
		Filler("[INFO] " + msg + "\n");
	}

	static void Filler(std::string msg)
	{
		std::cout << msg;
		std::cout.flush();

	}
};
