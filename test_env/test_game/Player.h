#pragma once
#include "VisibleGameObject.h"
#include "Map.h"
#include "stdafx.h"

#define DOWN    0
#define LEFT    1
#define RIGHT   2
#define UP      3

#define X       0
#define Y       1

class Player :
	public VisibleGameObject
{
public:
	Player(bool controllable);
	~Player();

	void Update(float elapsedTime, Map * m);
    void Draw(sf::RenderWindow& rw);
    
    float GetVelocity() const;

    struct PlayerData {

        std::string id;

        float xPos;
        float yPos;

        int action;
    };

    void SendNetworkRequest(PlayerData pd);

    void MovePlayer(float x, float y);

private:

    sf::SocketTCP Sender;

    bool controllable;

    float _xVelocity;  // -- left ++ right
    float _yVelocity;  // -- left ++ right 
    int animationCount;

    float handleCollision(sf::Vector2f vf, Map *map);
    
    void calcDistance(float &distance, Map *map, float playerPosition[], float cheapCleanArray[], int edgeAxes, int j);

    // Will find the tiles with which the forward facing edge intersects, 
    // placing it in the InterTiles array.
    void getIntersectingTiles(sf::Vector2f InterTiles[], int &length, sf::Vector2f FFEdge, int edgeAxes);


    int animate(int verticalOffset, int i);
    int _playerDirection;
};

