#include "StdAfx.h"
#include "Player.h"
#include "Game.h"
#include "GameObjectManager.h"

#define spriteH 32
#define spriteW 32
#define walkDelay 15
#define movementSpeed  150.0f

Player::Player() :
_xVelocity(0),
_yVelocity(0),
animationCount(0)
{
	Load("images/Evil.png");
	assert(IsLoaded());

	GetSprite().SetCenter(GetSprite().GetSize().x /2, GetSprite().GetSize().y / 2);

}

Player::~Player()
{
}

void Player::Draw(sf::RenderWindow & rw)
{
	VisibleGameObject::Draw(rw);
}

float Player::GetVelocity() const
{
	return _xVelocity;
}

bool handleCollision(sf::Vector2f &position) {

}

void Player::Update(float elapsedTime)
{

	if(Game::GetInput().IsKeyDown(sf::Key::Left))
	{
		_xVelocity = -movementSpeed;
		animationCount = animate(1, animationCount);	
	} 
	else if(Game::GetInput().IsKeyDown(sf::Key::Right))
	{
		_xVelocity =  movementSpeed;
		animationCount = animate(2, animationCount);
	}
	else
	{
		_xVelocity = 0.0f;
	}

	if(Game::GetInput().IsKeyDown(sf::Key::Up))
	{
		_yVelocity = -movementSpeed;
		animationCount = animate(3, animationCount);
	} 
	else if(Game::GetInput().IsKeyDown(sf::Key::Down))
	{
		_yVelocity =  movementSpeed;
		animationCount = animate(0, animationCount);
	}
	else
	{
		_yVelocity = 0.0f;
	}

	sf::Vector2f pos = this->GetPosition();

	//handlePosition(pos);

	/* Wrapping on edge of map */

	if(pos.x > Game::SCREEN_WIDTH + GetSprite().GetSize().x/2 && Game::GetInput().IsKeyDown(sf::Key::Right))
	{
		SetPosition((0 - GetSprite().GetSize().x/2), pos.y); 
	}

	if(pos.x  < 0 - GetSprite().GetSize().x/2  && Game::GetInput().IsKeyDown(sf::Key::Left))
	{
		SetPosition((Game::SCREEN_WIDTH + GetSprite().GetSize().x/2), pos.y);
	}

	if(pos.y > Game::SCREEN_HEIGHT + GetSprite().GetSize().y/2 && Game::GetInput().IsKeyDown(sf::Key::Down))
	{
		SetPosition(pos.x, (0 - GetSprite().GetSize().y/2));
	}

	if(pos.y < 0 - GetSprite().GetSize().y/2  && Game::GetInput().IsKeyDown(sf::Key::Up))
	{
		SetPosition(pos.x, (Game::SCREEN_HEIGHT + GetSprite().GetSize().y/2)); 
	}	
	
	GetSprite().Move(_xVelocity * elapsedTime, _yVelocity * elapsedTime);
}

/* This is so hacky. Please don't judge me QQ */
int Player::animate(int verticalOffset, int i) {
	int j = i / walkDelay;
	sf::IntRect frame(0, 0, spriteW, spriteH);
	frame.Offset(j*spriteW, verticalOffset*spriteH);
	GetSprite().SetSubRect(sf::IntRect(frame));
	return (i + 1) % (walkDelay * 3);
}