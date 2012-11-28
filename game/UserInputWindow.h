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


	void ProcessUserInput();

	const static int SCREEN_WIDTH = 512;
	const static int SCREEN_HEIGHT = 512;

	
	bool UpdateView();
	friend class RenderEngine;
private:

	bool Initialize();
	sf::RenderWindow _window;
	int cam_x;
};