

#include "UserInputWindow.h"
#include "Common.h"



UserInputWindow::UserInputWindow()
{
	Initialize();
}

bool UserInputWindow::Initialize()
{
	//Setup the 
	_window.Create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Zombies OP - Client");
	_window.SetFramerateLimit(60);
	_window.Clear(sf::Color(200,200,200));

	//Setup the RenderEngine

}


//Update the users render of the game.
bool UserInputWindow::UpdateView()
{


}

