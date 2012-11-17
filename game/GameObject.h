#include "Common.h"

class GameObject
{
public:
	sf::Shape footprint;

	const int& id() const { return id_; }	//Getter
	void id(int& newId) { id_ = newId; } //Setter
	void draw();
	void update();

private:
	int id_;
	sf::Sprite sprite;
};