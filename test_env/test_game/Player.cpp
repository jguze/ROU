#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "GameObjectManager.h"

#define spriteH 32
#define spriteW 32
#define walkDelay 15
#define movementSpeed  150.0f

sf::Packet& operator << (sf::Packet& Packet, const Player::PlayerData& C) {
	return Packet << C.id << C.xPos << C.yPos << C.action;
}

Player::Player(bool c) :
_xVelocity(0),
_yVelocity(0),
animationCount(0),
_playerDirection(0)
{
	Load("images/Evil.png");
	assert(IsLoaded());

	controllable = c;

	GetSprite().SetCenter(GetSprite().GetSize().x /2, GetSprite().GetSize().y / 2);

}

Player::~Player()
{
}

void Player::Draw(sf::RenderWindow & rw)
{
	VisibleGameObject::Draw(rw);
}

void Player::MovePlayer(float x, float y) {
	GetSprite().Move(x, y);
}

void Player::SendNetworkRequest(PlayerData pd) {
	sf::IPAddress ServerAddress = sf::IPAddress(SERVER_IP);
	if(!Game::Client.Connect(PORT, ServerAddress)) {
		std::cout << "SendNetworkRequest";
		return;
	}

	sf::Packet Packet;

	Packet << pd;
	Game::Client.Send(Packet);
	std::cout << "\nPlayer: " << pd.id << " xPos: " << pd.xPos << " yPos: " << pd.yPos << " action: " << pd.action << "\n";
}


float Player::GetVelocity() const
{
	return _xVelocity;
}

void Player::calcDistance(float &distance, Map *map, float FFEdge[], float cheapCleanArray[], int edgeAxes, int j)
{
	int collidedTileType;
	if (edgeAxes == X)
	{
		collidedTileType = map->getCollisionType(sf::Vector2f(j*32, cheapCleanArray[!edgeAxes]*32));
	} else {
		collidedTileType = map->getCollisionType(sf::Vector2f(cheapCleanArray[!edgeAxes]*32, j * 32));
	}

	if (collidedTileType == Map::CLOSED_TILE)
	{
		float tempDist = abs(FFEdge[edgeAxes] - (j * 32)) - (_playerDirection == UP || _playerDirection == LEFT ? 32 : 0);
		if (tempDist < distance || distance <= -1)
		{
			distance = tempDist;
			std::cout << "Nearest collision tile: " << "| " << cheapCleanArray[!edgeAxes] << " | " << j << " |" << std::endl;
		}
	}
}

float Player::handleCollision(sf::Vector2f position, Map *map) {
	sf::Vector2f ForwFacingEdge;
	int edgeAxes;
	sf::Vector2f intersectingTiles[32];

	if (_playerDirection == UP)
	{
		ForwFacingEdge.x = position.x;
		ForwFacingEdge.y = position.y - 16; //OH SHIT HARD CODED WHAT AN ASSHOLE
		edgeAxes = Y;
	} else if (_playerDirection == DOWN) {
		ForwFacingEdge.x = position.x;
		ForwFacingEdge.y = position.y + 16;
		edgeAxes = Y;
	} else if (_playerDirection == LEFT) {
		ForwFacingEdge.x = position.x - 16;
		ForwFacingEdge.y = position.y;
		edgeAxes = X;
	} else if (_playerDirection == RIGHT) {
		ForwFacingEdge.x = position.x + 16; 
		ForwFacingEdge.y = position.y;
		edgeAxes = X;
	} else {
		//Impossible to get here
	}
	std::cout << "FFEdge Coords: " << ForwFacingEdge.x << " : " << ForwFacingEdge.y << std::endl;
	int length = 0;
	getIntersectingTiles(intersectingTiles, length, ForwFacingEdge, edgeAxes); // Finds all the tiles that intersect with the FFEdge

	int collidedTileType;
	float distance = -1;
	float FFEdge[] = {ForwFacingEdge.x, ForwFacingEdge.y};

	for (int i = 0; i < length; i++)
	{
		float cheapCleanArray[] = {intersectingTiles[i].x, intersectingTiles[i].y}; // Shuddap this is a major hack. Intersecting tiles is in xy coords, NOT PIXELS
		int j = (int) cheapCleanArray[edgeAxes]; // Again, complete hack so I can choose the proper fields by axes without if statements much.
		if (_playerDirection == UP || _playerDirection == LEFT)
		{
			for (; j >= 0; j--)
				calcDistance(distance, map, FFEdge, cheapCleanArray, edgeAxes, j);		
		} else {
			for (; j < 20; j++)
				calcDistance(distance, map, FFEdge, cheapCleanArray, edgeAxes, j);
		}
		//std::cout << distance << " : ";
	}
	//std::cout << std::endl;
	return distance;

	// switch (collidedTileType) {
	// 	case Map::OPEN_TILE:
	// 		break;
	// 	case Map::CLOSED_TILE:
	// 		_xVelocity  = 0.0f;
	// 		_yVelocity = 0.0f;
	// 		break;
	// 	case Map::UP_DIAGONAL_TILE:
	// 		if(_yVelocity < 0) {
	// 			_xVelocity = -_yVelocity;
	// 		}
	// 		break;
	// 	case Map::DOWN_DIAGONAL_TILE:
	// 		if(_yVelocity < 0) {
	// 			_xVelocity = _yVelocity;
	// 		}
	// 		break;
	// }
}

void Player::getIntersectingTiles(sf::Vector2f InterTiles[], int &length, sf::Vector2f FFEdge, int edgeAxes)
{
	int minTile;
	int maxTile;

	if (edgeAxes == X)
	{
		minTile = (int) ((FFEdge.y - 16) / 32); // DAFUQ JUSTIN MAKE USE THE TILE CONSTANTS
		maxTile = (int) ((FFEdge.y + 16) / 32);
	} else {
		minTile = (int) ((FFEdge.x - 16) / 32);
		maxTile = (int) ((FFEdge.x + 16) / 32);
	}

	int tile = minTile;
	for (length = 0; tile < maxTile + 1; tile++, length++)
	{
		if (edgeAxes == X)
		{
			sf::Vector2f v(FFEdge.x / 32, tile);
			InterTiles[length] = v;
		} else {
			sf::Vector2f v(tile, FFEdge.y / 32);
			InterTiles[length] = v;
		}
	}
}

void Player::Update(float elapsedTime, Map * map)
{
	if(controllable == true) {
		PlayerData data;

		if(Game::GetInput().IsKeyDown(sf::Key::Left))
		{
			_xVelocity = -movementSpeed;
			_playerDirection = LEFT;
			animationCount = animate(LEFT, animationCount);	
		} 
		else if(Game::GetInput().IsKeyDown(sf::Key::Right))
		{
			_xVelocity =  movementSpeed;
			_playerDirection = RIGHT;
			animationCount = animate(RIGHT, animationCount);
		}
		else
		{
			_xVelocity = 0.0f;
		}

		if(Game::GetInput().IsKeyDown(sf::Key::Up))
		{
			_yVelocity = -movementSpeed;
			_playerDirection = UP;
			animationCount = animate(UP, animationCount);
		} 
		else if(Game::GetInput().IsKeyDown(sf::Key::Down))
		{
			_yVelocity =  movementSpeed;
			_playerDirection = DOWN;
			animationCount = animate(DOWN, animationCount);
		}
		else
		{
			_yVelocity = 0.0f;
		}

		sf::Vector2f pos = this->GetPosition();

		float distToCollision = handleCollision(pos, map);

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

		if(Game::GetInput().IsKeyDown(sf::Key::Space)) {
			SetPosition(Game::SCREEN_WIDTH/2, Game::SCREEN_HEIGHT/2);
		}
		
		/* Move the sprite */
		//std::cout << distToCollision << std::endl;
		std::cout << "DISTANCETOSOLID: " << distToCollision << std::endl;
		if (distToCollision == -1) 
		{
			GetSprite().Move(_xVelocity * elapsedTime, _yVelocity * elapsedTime);

		} else {
			std::cout << "Collision Ahead" << std::endl;
			float finXDist = _xVelocity * elapsedTime;
			float finYDist = _yVelocity * elapsedTime;

			if (_playerDirection == UP || _playerDirection == DOWN)
			{
				finYDist = std::abs(_yVelocity * elapsedTime) < distToCollision ? _yVelocity * elapsedTime : (_playerDirection == UP ? 1 : -1) * distToCollision;
			} else {
				finXDist = std::abs(_xVelocity * elapsedTime) < distToCollision ? _xVelocity * elapsedTime : (_playerDirection == RIGHT ? 1 : -1) * distToCollision;
			}
			std::cout << "XD: " << finXDist << " YD: " << finYDist << std::endl;
			GetSprite().Move(finXDist, finYDist);
		}

		data.xPos = pos.x;
		data.yPos = pos.y;
		data.action = 0;

		if(CLIENT) {
			data.id = "Client"; // TODO don't hard code this shit
			SendNetworkRequest(data);
		}	
	}
}

/* This is so hacky. Please don't judge me QQ */
int Player::animate(int verticalOffset, int i) {
	int j = i / walkDelay;
	sf::IntRect frame(0, 0, spriteW, spriteH);
	frame.Offset(j*spriteW, verticalOffset*spriteH);
	GetSprite().SetSubRect(sf::IntRect(frame));
	return (i + 1) % (walkDelay * 3);
}
