#include <iostream>
#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"


Map* map;
Manager manager;

SDL_Renderer* Game::renderer = __nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

auto& tile0(manager.addEntity());
auto& tile1(manager.addEntity());
auto& tile2(manager.addEntity());

Game::Game() {}
Game::~Game() {}
//Инициализация игры: создание окна е
void Game::init(const char* p_title, int xpos, int ypos,int width,int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialised" << std::endl;

		window = SDL_CreateWindow(p_title, xpos, ypos, width, height, flags);
		if (window) {
			std::cout << "Window created" << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			std::cout << "Renderer created" << std::endl;
		}
		isRunning = true;
	}
	map = new Map();

	//ECS штуки
	tile0.addComponent<TileComponent>(200,200,35,35,0);
	tile1.addComponent<TileComponent>(250,250,35,35,1);
	tile1.addComponent<ColliderComponent>("dirt");
	tile2.addComponent<TileComponent>(150,150,35,35,2);
	tile2.addComponent<ColliderComponent>("grass");

	player.addComponent<TransformComponent>(2);
	player.addComponent<SpriteComponent>("Assets/Doock.png");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");

	wall.addComponent<TransformComponent>(300.f, 300.f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("Assets/dirt.png");
	wall.addComponent<ColliderComponent>("wall");
}
//Эвенты для окна 
void Game::handleEvents() {
	
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT://Если нажаи крестик на окне
		isRunning = false;
		break;
	default:
		break;
	}
}
void Game::update() {
	manager.referesh();
	manager.update();
	if (player.getComponent<TransformComponent>().position.x > 300) {
		player.getComponent<SpriteComponent>().setTex("Assets/Enemy.png");
	}
	for (auto cc : colliders) {
		Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
	}
}
void Game::render() {
	SDL_RenderClear(renderer);
	//тут будем добавлять штуки на рендер в порядке наслаивания
		//map->DrawMap();
	manager.draw();
	SDL_RenderPresent(renderer);
}
//Очистка памяти
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}

