#pragma once
#include "Components.h"
#include"SDL.h"

class SpriteComponent: public Component {
private:
	PositionComponenet* position;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
public:
	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		texture = TextureManager::LoadTexture(path);
	}
	void init() override{
		position = &entity->getComponent<PositionComponenet>();
		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 35;
		destRect.w = destRect.h = 35 * 2;
	}
	void update() override {
		destRect.x = position->x();
		destRect.y = position->y();
	};
	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect);
	};

};