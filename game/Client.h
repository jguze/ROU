
/*
---- Client ----
Client is the main game loop of the client program. 
It is responsible for taking input from the 
UserInputWindow and translating it to the game object
manager. 


*/
#pragma once
#include "Common.h"
#include "UserInputWindow.h"
#include "Renderer.h"

class Client
{
public:
	Client();
	bool Initialize();
	// cameraView will be 2 floats representing the top
	// left corner of the window. This will be fed to the
	// renderer
	void GameLoop();
	Position cameraView();
	void ProcessEvent(const sf::Event & event);
	bool isRunning;
private:
	enum ClientState { Unitialized, Active, Exiting};
	ClientState _state;
	Renderer * _renderer;
	UserInputWindow * window;
	// Move player out of here for later
	GameObject* _player;
};