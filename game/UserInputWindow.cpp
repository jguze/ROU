#include "UserInputWindow.h"

UserInputWindow::UserInputWindow() 
{
	Initialize();
}

bool UserInputWindow::Initialize()
{

	renderWindow.Create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Zombies OP - Client");
	renderWindow.SetFramerateLimit(60);
	renderWindow.Clear(sf::Color(200,200,200));
}