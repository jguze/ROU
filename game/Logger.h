

#pragma once
#include <stdio.h>
#include <string>

class Logger
{
public:

	static void LogError(string msg)
	{
		Filler(msg);
	}

	static void LogWarn(string msg)
	{
		Filler(msg);
	}

	static void LogDebug(string msg)
	{
		Filler(msg);
	}

	static void LogInfo(string msg)
	{
		Filler(msg);
	}

	static void Filler(string msg)
	{
		std::cout << msg;
		std::cout.flush();

	}


};