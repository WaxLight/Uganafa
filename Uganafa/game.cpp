#include <iostream>
#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include <sstream>

Map* map;
Manager manager;
AssetManager* Game::assets = new AssetManager(&manager);

SDL_Renderer* Game::renderer = __nullptr;
SDL_Event Game::event;

 bool Game::isRunning=false;

 SDL_FRect Game::camera = { 0,0,480.f*2,270.f*2 };

auto& player(manager.addEntity());
auto& label(manager.addEntity());

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
	if (TTF_Init() == -1) {
		std::cout<<"Error : SDL_TTF\n";
	}
	assets->AddTexture("map", "Assets/TXTilesetGrass.png");
	assets->AddTexture("player", "Assets/Doock_anim.png");
	assets->AddTexture("projectile", "Assets/proj.png");

	assets->AddFont("rob","Assets/Roboto.ttf",16);

	map = new Map("map", 2, 32);

	//ECS штуки
	std::cout << "Map started "<< std::clock()<<std::endl;
	map->LoadMap(25, 20);
	std::cout << "Map loaded\n";

	player.addComponent<TransformComponent>(0,0,32,32,3);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);
	std::cout << "PlayerCreated\n";

	SDL_Color white = { 255,255,255,255 };
	label.addComponent<UILabel>(400, 0, "", "rob", white);

	assets->CreateObjects(Vector2D(32.f, 0.f), Vector2D(-1.f, 0.f), 600, 1, "projectile");
	//assets->CreateObjects(Vector2D(0, 0), Vector2D(0, 1), 600, 1, "projectile");
	//assets->CreateObjects(Vector2D(0, 0), Vector2D(1, 0), 600, 1, "projectile");
	assets->CreateObjects(Vector2D(32.f, 0.f), Vector2D(0.f, -1.f), 600, 1, "projectile");
	//assets->CreateObjects(Vector2D(0.f, 0.f), Vector2D(0.f, 0.f), 6400, 0, "projectile");
	std::cout << "ProjectileCreated\n";
}
auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));
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

	std::stringstream ss;
	ss << "Player position " << playerPos;;

	label.getComponent<UILabel>().SetLabelText(ss.str(), "rob");

	manager.referesh();
	manager.update();

	for (auto& c : colliders) {
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol)) {
			player.getComponent<TransformComponent>().position = playerPos;
		}
	}
	for (auto& p : projectiles) {
		if (Collision::AABB(playerCol, p->getComponent<ColliderComponent>().collider)) {
			std::cout << "player hit\n";//p->destroy();
		}
	}

	camera.x = player.getComponent<TransformComponent>().position.x - 480.f ;
	camera.y = player.getComponent<TransformComponent>().position.y - 270.f ;

	
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
	for (auto& p : projectiles) {
		p->draw();
	}
	label.draw();
	SDL_RenderPresent(renderer);
}
//Очистка памяти
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}

