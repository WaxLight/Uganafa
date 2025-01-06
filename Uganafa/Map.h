#pragma once

class Map {
public:
	Map(const char* mf, int ms, int ts);
	~Map();

	void LoadMap( int sizeX,int sizeY);
	void AddTile(int srcX, int srcY, int xpos, int ypos);
private:
	const char* mapFile;
	int mapScale;
	int tileSize;
	int scaledSize;
};