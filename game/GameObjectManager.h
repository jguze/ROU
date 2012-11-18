#include "Common.h"
#include "GameObject.h"
#include <hash_map>
#pragma once
#include <list>
#include "GameObject.h"

#define MAX_NUM_PARTITIONS_WIDTH	100
#define MAX_NUM_PARTITIONS_HEIGHT	100

class GameObjectManager
{
public:
	// This is a 2d array of lists of GameObjects. Essentially, to make looking
	// up what to draw easier, every objects acutal pixel position will be converted
	// to an integer that can be looked up in this. Essentially, the map will 
	// be cut into arbitary squares we will use just for this. Then, given a screen
	// to look at, we can look up the game objects that need to be drawn, rather
	// than look at all game objects.
	// EXAMPLE: Assume our map is 
	//std::list<GameObject>[MAX_NUM_PARTITIONS_WIDTH][MAX_NUM_PARTITIONS_HEIGHT] gameObjectArray;

	std::list<GameObject>* getObjectsToDraw(Position cameraView);
};