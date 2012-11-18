#include "Renderer.h"

Renderer::Renderer(sf::RenderWindow & rw, GameObjectManager * gameObjectManager)
{
	_renderWindow = rw;
	_gameObjectManager = gameObjectManager;
}

Renderer::~Renderer()
{
}

void Renderer::draw(Position cameraView)
{
	//Draw everything that the client currently is looking at
	//NOTE: Every drawable sfml object has these:
	// 	sf::Sprite Sprite;
	// Sprite.SetColor(sf::Color(0, 255, 255, 128));
	// Sprite.SetX(200.f);
	// Sprite.SetY(100.f);
	// Sprite.SetPosition(200.f, 100.f);
	// Sprite.SetRotation(30.f);
	// Sprite.SetCenter(0, 0);
	// Sprite.SetScaleX(2.f);
	// Sprite.SetScaleY(0.5f);
	// Sprite.SetScale(2.f, 0.5f);
	// Sprite.SetBlendMode(sf::Blend::Multiply);

	// Sprite.Move(10, 5);
	// Sprite.Rotate(90);
	// Sprite.Scale(1.5f, 1.5f);

	std::list<GameObject>* gameObjectList = _gameObjectManager->getObjectsToDraw(cameraView);
	std::list<GameObject>::iterator it;
	for (it = gameObjectList->begin(); it != gameObjectList->end(); it++)
	{
		// Must first edit sprite x and y values to be appropriate to the
		// window placement.
		// *it->sprite().draw(_renderWindow);
		_renderWindow.Draw(it->sprite());
	}
}