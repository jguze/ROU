#pragma once
#include "Common.h"
#include "GameObjectManager.h"

class Renderer
{
public:
	Renderer(sf::RenderWindow & rw,
		GameObjectManager * gameobjectManager);
	~Renderer();
	void draw(Position cameraView);

private:
	sf::RenderWindow  _renderWindow;
	GameObjectManager * _gameObjectManager;
};