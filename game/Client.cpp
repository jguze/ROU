#include "Client.h"
Client::Client()
{
	//_state = Uninitialized;
	Initialize();
	GameLoop();
}

/*
Setup the Client to play the game
This includes:
	Establishing a connection to the server
	Creating the game window

*/
bool Client::Initialize()
{
	//if(_state != Uninitialized) return;

	window = new UserInputWindow();

	// Create Player object, and set coordinates.
	_player = new GameObject();
	_player->position.x = 512 / 2;
	_player->position.y = 512 / 2;
	GameObjectManager* obj = new GameObjectManager();
	_renderer = new Renderer(window->renderWindow, obj);
	return true;
}

// DECIDE WHERE WE"RE DOING ALL THE GAME LOGIC
void Client::GameLoop()
{
	sf::Event event;
	isRunning = true;
	while(isRunning)
	{	
		// Drain the event queue
		while(window->renderWindow.GetEvent(event))
		{
			ProcessEvent(event);
		}
		_renderer->draw(cameraView());
	}
}

void Client::ProcessEvent(const sf::Event & event)
{
	// TODO: Implement this
	if (event.Type == sf::Event::Closed)
		isRunning = false;
}

Position Client::cameraView()
{
	Position camera;
	// TODO: Should determining if the map is looping be done
	// here, on at the rendering stage? Figure out how
	// looping will work, if we choose to have it.
	camera.x = _player->position.x - SCREEN_WIDTH;
	camera.y = _player->position.y - SCREEN_HEIGHT;
	return camera;
}