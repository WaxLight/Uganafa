#include <iostream>
#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"


Map* map;
Manager manager;
SDL_Renderer* Game::renderer = __nullptr;

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
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			std::cout << "Renderer created" << std::endl;
		}
		isRunning = true;
	}
	map = new Map();
	player.addComponent<PositionComponenet>();
	player.addComponent<SpriteComponent>("Assets/Doock.png");
}
//Эвенты для окна 
void Game::handleEvents() {
	SDL_Event event;
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

	if (player.getComponent<PositionComponenet>().x() > 100) {
		player.getComponent<SpriteComponent>().setTex("Assets/Enemy.png");
	}
}
void Game::render() {
	SDL_RenderClear(renderer);
	//тут будем добавлять штуки на рендер в порядке наслаивания
	map->DrawMap();
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

