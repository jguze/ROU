/*
UserInputWindow
This the main window that the user sees 
while they are playing the game. It handles
Input from the screen and keyboard for the
Client
It uses the SFML Render Window as its base.



*/


#pragma once
#include "Common.h"

class UserInputWindow
{

public: 

	UserInputWindow();
	bool Initialize();
	sf::RenderWindow renderWindow;

private:
};