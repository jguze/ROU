#include "Common.h"
#include "Client.h"

Client::Client()
{
	//_state = Uninitialized;
	Initialize();
	
}

/* Establish a connection to the server */
bool Client::ConnectToServer() {
	sf::IPAddress serverAddress = sf::IPAddress(SERVER_IP);
	if(client.Connect(PORT, serverAddress) != sf::Socket::Done) {
		Logger::LogError("Cannot connect to server.");
		std::cout.flush();
		return false;
	}

	Logger::LogInfo("Connected to server.");
	return true;
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

	ConnectToServer();
	_uiw = new UserInputWindow();
	_state = Active;
	return true;
}

void Client::Run()
{
	Logger::LogInfo("Client has stated.");
	while(_state == Active)
	{
		//Handle User Input

		//Send Shit to the Server

		//Receive Shit from Server

		//Update My View
		_uiw->Update();

	}
}







