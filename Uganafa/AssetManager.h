#pragma once
#include<map>
#include<string>
#include "TextureManager.h"
#include "Vector2D.h"
#include"ECS/ECS.h"
#include "SDL_ttf.h"

class AssetManager {
public:
	AssetManager(Manager* man);
	~AssetManager();

	//game Objects

	void CreateObjects(Vector2D pos,Vector2D vel,int range,int speed,std::string);

	//texture managment
	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);

	//font managment
	void AddFont(std::string id, std::string path, int fontSize);
	TTF_Font* GetFont(std::string id);
private:
	Manager* manager;

	std::map<std::string, SDL_Texture*> textures;

	std::map<std::string, TTF_Font*> fonts;
};