#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "GameObjectManager.h"
#include "Map.h"

class Game
{

public:

	static void Start();
	static sf::RenderWindow& GetWindow();
	const static sf::Input& GetInput();
	const static int SCREEN_WIDTH = 640;
	const static int SCREEN_HEIGHT = 640;

	static sf::SocketTCP Client;
	static sf::SocketTCP Server;

private:
	static bool IsExiting();
	static void GameLoop();

	static void GetServerResponse();
	static void ProcessClientResponse();

	static void RunServer();
	static void RunClient();

	enum GameState { Uninitialized, Playing, Exiting };

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;
	
	static GameObjectManager _gameObjectManager;
};
