#pragma once
#include<string>
class Map {
public:
	Map(std::string tID, int ms, int ts);
	~Map();

	void LoadMap();
	void AddTile(int srcX, int srcY, int xpos, int ypos);
	void AddWallColl(int x, int y, bool horiz);

private:
	std::string texID;
	int mapScale;
	int tileSize;
	int scaledSize;

};