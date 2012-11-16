#pragma once
#include "VisibleGameObject.h"
#include "Map.h"


class GameObjectManager
{
public:	
	GameObjectManager();
	~GameObjectManager();

	void Add(int id, VisibleGameObject* gameObject);
	void Remove(int id);
	int GetObjectCount() const;
	VisibleGameObject* Get(int id) const;

	void DrawAll(sf::RenderWindow& renderWindow);
	void UpdateAll();

	Map *map;

private:
	std::map<int, VisibleGameObject*> _gameObjects;

	struct GameObjectDeallocator
	{
		void operator()(const std::pair<int,VisibleGameObject*> & p) const
		{
			delete p.second;
		}
	};
};