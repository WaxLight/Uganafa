#include "Map.h"
#include "Game.h"
#include"ECS/ECS.h"
#include"ECS/Components.h"
#include<random>
#include<iostream>
#include<vector>

int nextCell(int pos, int size);
void connect(int pos1, int pos2);
void randomdfs(int pos, int size);
void createMazeDFS();

//mazeCreation
const int size = 16;
std::vector<bool> visited;
//std::vector<bool, bool> walls;
bool walls[size * size][2]; //0 for a wall, 1 for no wall left -> top

extern Manager manager;

Map::Map(std::string tID, int ms, int ts) :texID(tID), mapScale(ms), tileSize(ts)
{

	scaledSize = ms * ts;

}
Map::~Map() {
}
void Map::LoadMap()
{
    
    createMazeDFS();
    std::random_device rd;
    std::uniform_int_distribution<int> distG(0, 3);
    std::uniform_int_distribution<int> distM(3, 7);
 
    //for (int y=0; y < sizeY; y++) {
    //    for (int x=0; x < sizeX; x++) {
    //        AddTile(distG(rd) * tileSize, distG(rd) * tileSize, x * scaledSize, -y * scaledSize);
    //        AddTile(distG(rd) * tileSize, distG(rd) * tileSize, -x * scaledSize, y * scaledSize);
    //    }
    //}
    scaledSize *= 2;
    mapScale *= 2;
   /* tcol.addComponent<ColliderComponent>("zemla", 0, 0, scaledSize , scaledSize);
    tcol.addGroup(Game::groupColliders);*/
    auto& ecol(manager.addEntity());
    ecol.addComponent<ColliderComponent>("win", (size - 1) * scaledSize + scaledSize / 4, (size - 1) * scaledSize + scaledSize / 4, scaledSize/2);
    ecol.addGroup(Game::groupColliders);
    for (int j = 0, y=size-1; j < size; j++,y--) {
        for (int i = 0,x=size-1; i < size; i++,x--) {
            
            // j is y
            // i is x
            

            //vertical walls
            if ( i==size-1) {
                AddWallColl(x, y, false);
            }
            if (walls[i + j * size][0] == 0) {
                AddWallColl(x+1, y, false);
            }

            //horizontal walls
            if (j==size-1) {
                AddWallColl(x , y, true);
            }
            if (walls[i + j * size][1] == 0 /*|| j == 0 && i != 0*/) {
                AddWallColl(x, y+1, true);
            }
            AddTile(distG(rd) * tileSize, distM(rd) * tileSize, i * scaledSize, j * scaledSize);
        }
    }
    scaledSize /= 2;
    mapScale /= 2;
	
	std::cout << "loaded in " << std::clock() << "\n";
}
void Map::AddTile(int srcX, int srcY, int xpos, int ypos) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, texID);
	tile.addGroup(Game::groupMap);
}

void Map::AddWallColl(int x,int y,bool horiz){
    auto& wcol(manager.addEntity());
    (horiz) ?
        (wcol.addComponent<ColliderComponent>("wall", x * scaledSize, y * scaledSize - scaledSize / 16, scaledSize, scaledSize / 8)) :
        wcol.addComponent<ColliderComponent>("wall", x * scaledSize - scaledSize / 16, y * scaledSize, scaledSize / 8, scaledSize);
    wcol.addGroup(Game::groupColliders);
}


//mazeCreation
int nextCell(int pos, int size) {

    int optionCount = 0;
    int options[4];
    

    if (pos > size) { if (visited[pos - size] == 0) { options[optionCount] = -size; optionCount++; } }
    if ((pos + 1) % size != 0) { if (visited[pos + 1] == 0) { options[optionCount] = 1; optionCount++; } }
    if (pos < size * (size - 1)) { if (visited[pos + size] == 0) { options[optionCount] = size; optionCount++; } }
    if (pos % size != 0) { if (visited[pos - 1] == 0) { options[optionCount] = -1; optionCount++; } }

    if (optionCount == 0) { return 0; };
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, optionCount-1);
    int k = dist(rd);
        return (options[k]);
}
void connect(int pos1, int pos2) {
    if (pos2 > pos1) {
        if (pos2 == pos1 + 1) {
            walls[pos2][0] = 1;
        }
        else {
            walls[pos2][1] = 1;
        }
    }
    else {
        if (pos1 == pos2 + 1) {
            walls[pos1][0] = 1;
        }
        else {
            walls[pos1][1] = 1; 
        }
    }
}
void randomdfs(int pos, int size) {
    //std::cout << pos;
    visited[pos] = 1;
    int next = pos + nextCell(pos, size);
    while (next != pos) {
        connect(pos, next);
        pos = next;
        randomdfs(pos, size);
        next = pos + nextCell(pos, size);
    }
}

void createMazeDFS() {
    visited.clear();
    int pos = 0;
    for (int i = 0; i < size * size; i++) {
        visited.emplace_back(0);
        
        walls[i][0]= walls[i][1] = 0;
        
    }

    
    randomdfs(pos, size);
}

