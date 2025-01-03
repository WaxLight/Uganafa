#include "Map.h"
#include "TextureManager.h"

int lvl[20][25] = { 0 };
Map::Map() {
	dirt = TextureManager::LoadTexture("Assets/dirt.png");
	grass = TextureManager::LoadTexture("Assets/grass.png");
	water = TextureManager::LoadTexture("Assets/water.png");
	LoadMap(lvl);
	src.x = src.y = 0;
	src.h = dest.h =35;
	src.w = dest.w = 35;

	dest.x = dest.y = 0;


}
void Map::LoadMap(int arr[20][25]) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 25; j++)
			map[i][j] = arr[i][j];
	}
}
void Map::DrawMap(){
	int type = 0;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 25; j++) {
			type = map[i][j];
			dest.x = j * 35;
			dest.y = i * 35;
			switch (type) {
			case 0: 
				TextureManager::Draw(water, src, dest);
				break;
			case 1:
				TextureManager::Draw(grass, src, dest);
				break;
			case 2:
				TextureManager::Draw(dirt, src, dest);
				break;
			default: break;
			}
		}
	}
}