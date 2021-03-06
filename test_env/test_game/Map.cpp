#include "stdafx.h"
#include "Map.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>

#define mapWidth 20
#define mapHeight 20
#define spriteH 32
#define spriteW 32

int collision[mapWidth][mapHeight];

Map::Map() {
	Load("images/BGM.png");
	initializeCollisionMap();
}

void Map::Load(std::string filename)
{
	_imageBackground.LoadFromFile(filename);
	_background.SetImage(_imageBackground);
}

void Map::Draw(sf::RenderWindow& renderWindow)
{
	renderWindow.Draw(_background);
}

int Map::getCollisionType(sf::Vector2f currentPosition){
	return collision[(int)(currentPosition.x/spriteW)][(int)(currentPosition.y/spriteH)];
}

void Map::initializeCollisionMap() {
	int i = 0;
	int j = 0;

	std::ifstream input;
	FILE *mapFile;
	input.open("maps/laziness.map");
	if(input == NULL) {
		printf("Could not open map file!");
	}
	
	while(input.good()) {
		char c = input.get();
		if(c == '\n') {
			i = 0;
			j++;
		}
		collision[i][j] = atoi(&c);
		i++;
	}
	input.close();
}
