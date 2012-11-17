
#include "Client.h"

Client::Client()
{
	//_state = Uninitialized;
	Initialize();
	
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

	_uiw = new UserInputWindow();
	return true;
}