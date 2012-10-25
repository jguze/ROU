#include "stdafx.h"
#include "Game.h"

void Game::Start(void)
{
	if(_gameState != Uninitialized)
		return;
	
	_mainWindow.Create(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32),"Test Game");
	
	//_mainWindow.SetFramerateLimit(60);

	Player *player1 = new Player();
	player1->SetPosition((SCREEN_WIDTH/2),(SCREEN_HEIGHT/2));
	
	_gameObjectManager.Add("Player",player1);

	_gameState= Game::Playing;


	while(!IsExiting())
	{
		GameLoop();
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

void Game::GameLoop()
{
	sf::Event currentEvent;
	_mainWindow.GetEvent(currentEvent);
	
	
	switch(_gameState)
	{
		case Game::Playing:
			{
				_mainWindow.Clear(sf::Color(0,0,0));

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