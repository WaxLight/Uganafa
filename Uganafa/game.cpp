#include <iostream>
#include "Game.h"
#include "TextureManager.h"
SDL_Texture* playerTex;
SDL_Rect srcR, destR;

Game::Game() {}
Game::~Game() {}
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
	playerTex = TextureManager::LoadTexture("Assets/Doock.png", renderer);
}
void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}
void Game::update() {
	destR.h = 32*3;
	destR.w = 32*3;

}
void Game::render() {
	SDL_RenderClear(renderer);
	//тут будем добавлять штуки на рендер
	SDL_RenderCopy(renderer, playerTex, NULL, &destR);
	SDL_RenderPresent(renderer);
}
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}

