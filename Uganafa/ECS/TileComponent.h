#pragma once
#include"ECS.h"
#include<SDL.h>
#include"Map.h"

class TileComponent : public Component {
public:
	SDL_Texture* texture;
	SDL_Rect srcRect, destREct;
	Vector2D position;

	TileComponent() = default;
	~TileComponent() {
		SDL_DestroyTexture(texture);
	}
	TileComponent(int srcx, int srcy, int xpos, int ypos,int tsize,int tscale, std::string id) {
		texture = Game::assets->GetTexture(id);

		position.x = static_cast<float>(xpos);
		position.y = static_cast<float>(ypos);

		srcRect.x = srcx;
		srcRect.y = srcy;
		srcRect.w = srcRect.h = tsize;

		destREct.x = xpos;
		destREct.y = ypos;
		destREct.w = destREct.h = tsize * tscale;
	};
	void draw() override {
		TextureManager::Draw(texture, srcRect, destREct, SDL_FLIP_NONE);
	}
	void update()override{
		destREct.x = static_cast<int>(position.x - Game::camera.x);
		destREct.y = static_cast<int>(position.y - Game::camera.y);
	}
};