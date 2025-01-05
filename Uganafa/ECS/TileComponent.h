#pragma once
#include"ECS.h"
#include<SDL.h>

class TileComponent : public Component {
public:
	SDL_Texture* texture;
	SDL_Rect srcRect, destREct;
	Vector2D position;
	TileComponent() = default;
	~TileComponent() {
		SDL_DestroyTexture(texture);
	}
	TileComponent(int srcx, int srcy, int xpos, int ypos, const char* path) {
		texture = TextureManager::LoadTexture(path);

		position.x = xpos;
		position.y = ypos;

		srcRect.x = srcx;
		srcRect.y = srcy;
		srcRect.w = srcRect.h = 32;

		destREct.x = xpos;
		destREct.y = ypos;
		destREct.w = destREct.h = 32*2;
	};
	void draw() override {
		TextureManager::Draw(texture, srcRect, destREct, SDL_FLIP_NONE);
	}
	void update()override{
		destREct.x = position.x - Game::camera.x;
		destREct.y = position.y - Game::camera.y;
	}
};