#pragma once
#include "../Game.h"
#include"ECS.h"
#include"Components.h"

#include<iostream>

class KeyboardController :public Component {
private:
	float s = 0, w = 0, d = 0, a = 0, len = 0;
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	
	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override {

		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				w = -1; break;
			case SDLK_s:
				s = 1; break;
			case SDLK_a:
				a = -1;
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL; break;
			case SDLK_d:
				d = 1; 
				sprite->spriteFlip = SDL_FLIP_NONE; break;
			default:
				break;
			}
		}
		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				w = 0; break;
			case SDLK_s:
				s = 0; break;
			case SDLK_a:
				a = 0;
				if (d)
					sprite->spriteFlip = SDL_FLIP_NONE; 
				break;
			case SDLK_d:
				d = 0;
				if (a)
					sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_ESCAPE:
				Game::isRunning = false; break;
			default:
				break;
			}
		}
		
		len = sqrt((s+w) * (s+w) + (d+a) * (d+a));
		if (len) {
			transform->velocity = { (d + a) / len,(s + w)/len };
			sprite->Play("Walk");
		}
		else 
		{
			transform->velocity.Zero();
			sprite->Play("Idle");
		}
	} 
};
