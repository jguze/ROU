#include "stdafx.h"
#include "GameObjectManager.h"
#include "Game.h"

GameObjectManager::GameObjectManager()
{
	map = new Map();
}

GameObjectManager::~GameObjectManager()
{
	std::for_each(_gameObjects.begin(),_gameObjects.end(),GameObjectDeallocator());
}

void GameObjectManager::Add(int id, VisibleGameObject* gameObject)
{
	_gameObjects.insert(std::pair<int,VisibleGameObject*>(id,gameObject));
}

void GameObjectManager::Remove(int id)
{
	std::map<int, VisibleGameObject*>::iterator results = _gameObjects.find(id);
	if(results != _gameObjects.end() )
	{
		delete results->second;
		_gameObjects.erase(results);
	}
}

VisibleGameObject* GameObjectManager::Get(int id) const
{
	std::map<int, VisibleGameObject*>::const_iterator results = _gameObjects.find(id);
	if(results == _gameObjects.end() )
		return NULL;
	return results->second;
	
}

int GameObjectManager::GetObjectCount() const
{
	return _gameObjects.size();
}


void GameObjectManager::DrawAll(sf::RenderWindow& renderWindow)
{

	std::map<int,VisibleGameObject*>::const_iterator itr = _gameObjects.begin();
	while(itr != _gameObjects.end())
	{
		itr->second->Draw(renderWindow);
		itr++;
	}
}

void GameObjectManager::UpdateAll()
{
	std::map<int,VisibleGameObject*>::const_iterator itr = _gameObjects.begin();
	float timeDelta = Game::GetWindow().GetFrameTime();

	while(itr != _gameObjects.end())
	{
		itr->second->Update(timeDelta, map);
		itr++;
	}
	
}