#include "Map.h"
#include "Game.h"
#include"ECS/ECS.h"
#include"ECS/Components.h"
#include<random>
#include<iostream>

extern Manager manager;

Map::Map(std::string tID, int ms, int ts) :texID(tID), mapScale(ms), tileSize(ts)
{
	scaledSize = ms * ts;

}
Map::~Map() {
}
void Map::LoadMap( int sizeX, int sizeY)
{

	std::random_device rd;
	std::uniform_int_distribution<int> dist(0, 7);
	for (int y = -sizeY; y < sizeY; y++) {
		for (int x = -sizeX; x < sizeX; x++) {
			int k = dist(rd);
			int m = dist(rd) * tileSize;
		AddTile(m, k * tileSize, x * scaledSize, y * scaledSize);
		if (k > 4 && x > 0 && y > 0) {
			auto& tcol(manager.addEntity());
			tcol.addComponent<ColliderComponent>("zemla", x * scaledSize, y * scaledSize,scaledSize);
			tcol.addGroup(Game::groupColliders);
		}
		}
	}
	std::cout << "loaded in " << std::clock() << "\n";
}
void Map::AddTile(int srcX, int srcY, int xpos, int ypos) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, texID);
	tile.addGroup(Game::groupMap);
}