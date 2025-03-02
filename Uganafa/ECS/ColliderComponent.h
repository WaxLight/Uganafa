#pragma once
#include <string>
#include <SDL.h>
#include "Components.h"

class  ColliderComponent :public Component
{
public:
	SDL_FRect collider;
	std::string tag;


	SDL_Texture* tex;//
	SDL_Rect srcR;
	SDL_FRect destR;//

	TransformComponent* transform;

	ColliderComponent(std::string t) {
		tag = t;
	}
	ColliderComponent(std::string t, float xpos, float ypos, float size) {
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = collider.w = size;
	}
	ColliderComponent(std::string t, float xpos, float ypos, float sizeW, float sizeH) {
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = sizeH;
		collider.w = sizeW;
	}
	void init() override {
		if (!entity->hasComponent<TransformComponent>()) {
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();
		if(tag=="wall"){

			tex = TextureManager::LoadTexture("Assets/TX wall.png");
			srcR = { 0,0,32,32 };
			destR = { collider.x,collider.y,collider.w,collider.h };
		}
		if (tag == "win") {
			tex = TextureManager::LoadTexture("Assets/proj.png");
			srcR = { 0,0,32,32 };
			destR = { collider.x,collider.y,collider.w,collider.h };
		}
	}
	void update() override {
		if (tag == "player") {
	//		collider.x = transform->position.x+7*transform->scale;
		//	collider.y = transform->position.y+7*transform->scale;
			//collider.w = transform->width * transform->scale;
			//collider.h = transform->height * transform->scale;
			collider.x = transform->position.x + transform->width -collider.w / transform->scale  ;
			collider.y = transform->position.y+transform->height*transform->scale-collider.h ;
			//std::cout << (-collider.h) << std::endl;
			//std::cout << (transform->height - collider.h) << std::endl;

		}

		destR.x = collider.x - Game::camera.x;
		destR.y = collider.y -Game::camera.y;
	}
	void draw() override {
		TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
	}

	SDL_FRect& ADD(const SDL_FRect& col2) {
		SDL_FRect col1 = this->collider;
		col1.h += col2.h;
		col1.w += col2.w;
		col1.x -= col2.w / 2;
		col1.y -= col2.h / 2;
		return col1;
	}
};