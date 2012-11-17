
/*
---- Client ----
Client is the main game loop of the client program. 
It is responsible for taking input from the 
UserInputWindow and translating it to the game object
manager. 


*/


#pragma once
#include "UserInputWindow.h"

class Client
{
public:

	Client();
	bool Initialize();

private:
	enum ClientState { Unitialized, Active, Exiting};
	ClientState _state;

	UserInputWindow * _uiw;

};