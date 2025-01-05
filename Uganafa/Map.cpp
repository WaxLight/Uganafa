#include "Map.h"
#include "Game.h"
#include<random>
#include<iostream>
//Загрузка тексткр и их параметров
Map::Map(){}
Map::~Map() {
}
void Map::LoadMap( int sizeX, int sizeY)
{
	std::random_device rd;
	std::uniform_int_distribution<int> dist(0, 7);
	for (int y = -sizeY; y < sizeY; y++) {
		for (int x = -sizeX; x < sizeX; x++) {
			Game::AddTile(dist(rd) *32, dist(rd) * 32, x * 32*2, y * 32*2);
		}
	}
}
