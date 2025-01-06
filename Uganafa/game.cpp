#include <iostream>
#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"

Map* map;
Manager manager;
AssetManager* Game::assets = new AssetManager(&manager);

SDL_Renderer* Game::renderer = __nullptr;
SDL_Event Game::event;

 bool Game::isRunning=false;

 SDL_Rect Game::camera = { 0,0,800,640 };

auto& player(manager.addEntity());

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
			SDL_SetRenderDrawColor(renderer, 114, 117, 27, 255);
			std::cout << "Renderer created" << std::endl;
		}
		isRunning = true;
	}
	assets->AddTexture("map", "Assets/TXTilesetGrass.png");
	assets->AddTexture("player", "Assets/Doock_anim.png");

	map = new Map("map", 2, 32);

	//ECS штуки
	std::cout << "Map started "<< std::clock()<<std::endl;
	map->LoadMap(25, 20);
	std::cout << "Map loaded\n";

	player.addComponent<TransformComponent>(2);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);
	std::cout << "PlayerCreated\n";
}
auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
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
	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;

	manager.referesh();
	manager.update();

	for (auto& c : colliders) {
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol)) {
			player.getComponent<TransformComponent>().position = playerPos;
		}
	}

	camera.x = player.getComponent<TransformComponent>().position.x - 800 / 2;
	camera.y = player.getComponent<TransformComponent>().position.y - 640 / 2;

	
}

void Game::render() {
	SDL_RenderClear(renderer);
	//тут будем добавлять штуки на рендер в порядке наслаивания
	for (auto& t : tiles) {
		t->draw();
		//std::cout << "Draw complete" << "\n";
	}
	for (auto& c : colliders) {
		c->draw();
	}
	for (auto& p : players) {
		p->draw();
	}
	
	SDL_RenderPresent(renderer);
}
//Очистка памяти
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}

