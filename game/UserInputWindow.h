/*
UserInputWindow
This the main window that the user sees 
while they are playing the game. It handles
Input from the screen and keyboard for the
Client
It uses the SFML Render Window as its base.



*/


#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class UserInputWindow
{

public: 

	UserInputWindow();

	static sf::RenderWindow& GetWindow();

	const static int SCREEN_WIDTH = 512;
	const static int SCREEN_HEIGHT = 512;

	bool Initialize();

private:

	sf::RenderWindow _window;

};