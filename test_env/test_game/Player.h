#pragma once
#include "VisibleGameObject.h"

class Player :
	public VisibleGameObject
{
public:
	Player();
	~Player();

	void Update(float elapsedTime);
    void Draw(sf::RenderWindow& rw);
    
    float GetVelocity() const;

private:
    float _xVelocity;  // -- left ++ right
    float _yVelocity;  // -- left ++ right 
    int animationCount;

    int animate(int verticalOffset, int i);
};