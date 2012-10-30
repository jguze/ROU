#pragma once

class Map {
public:
	Map();
	~Map();

	void Draw(sf::RenderWindow& rw);
	void Load(std::string);
	void initializeCollisionMap();

	float getCollisionType(sf::Vector2f);

private:
	sf::Sprite _background;
	sf::Image _imageBackground;
};