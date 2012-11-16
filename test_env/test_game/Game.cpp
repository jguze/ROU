#include "stdafx.h"
#include "Game.h"

void Game::RunServer() {
	if(!Server.Listen(PORT))
		return;

	std::cout << "Server is listening to port " << PORT << ", waiting for connections... " << std::endl;

	// Wait for connections
	sf::IPAddress ClientAddress;
	Server.Accept(fromClient, &ClientAddress);
	std::cout << "Client connected: " << ClientAddress << "\n";
}

void Game::RunClient() {
	sf::IPAddress ServerAddress = sf::IPAddress(SERVER_IP);
	if(!Client.Connect(PORT, ServerAddress)) {
		std::cout << "Cannot connect to server.";
		std::cout.flush();
		return;
	}

	std::cout << "Connected to server " << ServerAddress << "\n";
}

void Game::Start(bool server)
{
	if(_gameState != Uninitialized)
		return;

	if(server) {
		RunServer();
	} else {
		RunClient();
	}
	
	_mainWindow.Create(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32),"Test Game");
	
	_mainWindow.SetFramerateLimit(60);

	_mainWindow.Clear(sf::Color(0,0,0));

	// Differentiate between the two players
	Player *player = new Player(server);
	player->SetPosition((SCREEN_WIDTH/2),(SCREEN_HEIGHT/2));

	Player *player1 = new Player(!server);
	player1->SetPosition((SCREEN_WIDTH/2),(SCREEN_HEIGHT/3));	
	
	_gameObjectManager.Add(SERVER_PLAYER,player);
	_gameObjectManager.Add(CLIENT_PLAYER,player1);

	_gameState= Game::Playing;

	while(!IsExiting())
	{
		GameLoop(server);
	}

	_mainWindow.Close();
}

bool Game::IsExiting()
{
	if(_gameState == Game::Exiting) 
		return true;
	else 
		return false;
}


sf::RenderWindow& Game::GetWindow()
{
	return _mainWindow;
}

const sf::Input& Game::GetInput() 
{
	return _mainWindow.GetInput();
}

void Game::GetServerResponse() {
	sf::Packet Packet;
	Player::PlayerData pd;

	if(Client.Receive(Packet) != sf::Socket::Done) {
		std::cout << "GetServerResponse";
		return;
	}

	Packet >> pd.id >> pd.xPos >> pd.yPos >> pd.action;

	Player * modified = (Player *)_gameObjectManager.Get(pd.id);
	modified->MovePlayer(pd.xPos, pd.yPos);
}

void Game::ProcessClientResponse() {
	sf::Packet Incoming;
	sf::Packet Outgoing;
	Player::PlayerData pd;

	if(Server.Receive(Incoming) != sf::Socket::Done) {
		std::cout << "ProcessClientResponse";
		return;
	}

	Incoming >> pd.id >> pd.xPos >> pd.yPos >> pd.action;

	// Moving client's player
	Player * modified = (Player *)_gameObjectManager.Get(pd.id);
	modified->MovePlayer(pd.xPos, pd.yPos);

	Player * serverPlayer = (Player*)_gameObjectManager.Get(SERVER_PLAYER);

	sf::Vector2f pos = serverPlayer->GetPosition();

	pd.id = SERVER_PLAYER;
	pd.xPos = pos.x;
	pd.yPos = pos.y;
	pd.action = 0;

	Outgoing << pd.id << pd.xPos << pd.yPos << pd.action;

	// Server validation would take place here, but for now, we'll cheat and simply send it back
	Server.Send(Outgoing); // This should be processed by GetServerResponse on the client end.
}

void Game::GameLoop(bool server)
{
	sf::Event currentEvent;
	_mainWindow.GetEvent(currentEvent);
	
	
	switch(_gameState)
	{
		case Game::Playing:
			{
				// See what the server sends back as a response
				if(!server) {
					GetServerResponse();
				} else {
					// Grab commands from the server object directly
					ProcessClientResponse();
				}

				_gameObjectManager.map->Draw(_mainWindow);

				_gameObjectManager.UpdateAll();
				_gameObjectManager.DrawAll(_mainWindow);

				_mainWindow.Display();

				if(currentEvent.Type == sf::Event::Closed) _gameState = Game::Exiting;

				if(currentEvent.Type == sf::Event::KeyPressed)
					{
						if(currentEvent.Key.Code == sf::Key::Escape) _gameState = Game::Exiting;
					}

				break;
			}
	}
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;
sf::SocketTCP Game::Client;
sf::SocketTCP Game::fromClient;
sf::SocketTCP Game::Server;