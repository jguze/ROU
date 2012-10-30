#pragma once

class Map {
public:
	Map();
	~Map();

	void Draw(sf::RenderWindow& rw);
	void Load(std::string);
	void initializeCollisionMap();

	const static int OPEN_TILE = 0;
	const static int CLOSED_TILE = 1;
	const static int UP_DIAGONAL_TILE = 2;
	const static int DOWN_DIAGONAL_TILE = 3;

	int getCollisionType(sf::Vector2f map);

private:
	sf::Sprite _background;
	sf::Image _imageBackground;
};