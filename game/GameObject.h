#pragma once
#include "Common.h"

struct Position {
	float x;
	float y;
};

class GameObject
{
public:
	sf::Shape footprint;
	// An objects position on the map, represented in pixels.
	// We cannot rely on the value in sprite, because that
	// value is relative to our RenderWindow, and not what
	// the actual map size.
	Position position;

	const int& id() const { return _id; }	//Getter
	void id(int& newId) { _id = newId; } //Setter
	sf::Sprite sprite() { return _sprite; }
	void draw();
	void update();

private:
	int _id;
	// Can be a sprite. Just makes it open to
	// extension
	sf::Sprite _sprite;
};