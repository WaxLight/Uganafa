#include "Map.h"
#include "Game.h"
#include<random>

//Загрузка тексткр и их параметров
Map::Map(){}
Map::~Map() {
}
void Map::LoadMap( int sizeX, int sizeY)
{
	std::random_device rd;
	std::uniform_int_distribution<int> dist(0, 2);
	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			Game::AddTile(dist(rd), x*35, y*35);
		}
	}
}
