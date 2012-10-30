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

private:
	static bool IsExiting();
	static void GameLoop();

	enum GameState { Uninitialized, Playing, Exiting };

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;
	
	static GameObjectManager _gameObjectManager;
};
