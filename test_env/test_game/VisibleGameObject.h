#pragma once
#include "Map.h"

class VisibleGameObject
{
public:
	VisibleGameObject();
	virtual ~VisibleGameObject();
	
	virtual void Load(std::string filename);
	virtual void Draw(sf::RenderWindow & window);
	virtual void Update(float elapsedTime, Map *map);

	virtual void SetPosition(float x, float y);
	virtual sf::Vector2f GetPosition() const;
	virtual bool IsLoaded() const;

protected:
	sf::Sprite& GetSprite();

private:
	sf::Sprite  _sprite;
	sf::Image _image;
	std::string _filename;
	bool _isLoaded;
};
