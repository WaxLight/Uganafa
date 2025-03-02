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
 bool Game::pause = false;

 SDL_FRect Game::camera = { 0,0,480.f*2,270.f*2 };

auto& player(manager.addEntity());
auto& label(manager.addEntity());
auto& label1(manager.addEntity());

auto& temp(manager.addEntity());

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
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);//(renderer, 114, 117, 27, 255);
			std::cout << "Renderer created" << std::endl;
		}
		isRunning = true;
	}
	if (TTF_Init() == -1) {
		std::cout<<"Error : SDL_TTF\n";
	}
	SDL_SetWindowIcon( window,IMG_Load("Assets/icon.png"));
	
	assets->AddTexture("map", "Assets/TXTilesetGrass.png");
	assets->AddTexture("player", "Assets/Doock_anim.png");
	assets->AddTexture("projectile", "Assets/proj.png");

	assets->AddFont("rob","Assets/Roboto.ttf",16);

	map = new Map("map", 2, 32);

	//ECS штуки
	std::cout << "Map started "<< std::clock()<<std::endl;
	map->LoadMap();
	std::cout << "Map loaded\n";

	player.addComponent<TransformComponent>(0,0,32,32,2);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player",0,0,20*player.getComponent<TransformComponent>().scale, 25*player.getComponent<TransformComponent>().scale);
	player.addGroup(groupPlayers);
	std::cout << "PlayerCreated\n";

	temp.addComponent<ColliderComponent>("wall", 0, 0, 0, 0);

	SDL_Color white = { 255,255,255,255 };
	label.addComponent<UILabel>(400, 0, "", "rob", white);
	label1.addComponent<UILabel>(200, 30, "", "rob", white);

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
	case SDL_QUIT://Если нажали крестик на окне
		isRunning = false;
		break;
	case SDL_KEYUP:
		if (event.key.keysym.sym == SDLK_p)
			pause = !pause;
		break;
	default:
		break;
	}
}
void Game::update() {
	SDL_FRect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;
	Vector2D playerOldVel= player.getComponent<TransformComponent>().velocity*player.getComponent<TransformComponent>().speed;

	std::stringstream ss;
	std::stringstream ss1;
	
	
	//for (auto& c : colliders) {
	//if (player.getComponent<TransformComponent>().TargetX() + (player.getComponent<ColliderComponent>().collider.w - 32 + 20 /*- 1*/) * player.getComponent<TransformComponent>().scale >= c->getComponent<ColliderComponent>().collider.x &&
	//	c->getComponent<ColliderComponent>().collider.x + c->getComponent<ColliderComponent>().collider.w >= player.getComponent<TransformComponent>().TargetX()) {
	//	std::cout << "xddd\n";
	//	player.getComponent<TransformComponent>().position.x = c->getComponent<ColliderComponent>().collider.x - (player.getComponent<ColliderComponent>().collider.w - 32 + 20 - 1) * player.getComponent<TransformComponent>().scale;
	//}
//		if (true) {}
//	}
	
	manager.referesh();
	manager.update();
	ss << "Player position " << playerCol.x << " "<<playerCol.w << " " << playerCol.y << " "<<playerCol.h;
	label.getComponent<UILabel>().SetLabelText(ss.str(), "rob");
	Vector2D playerVel = player.getComponent<TransformComponent>().velocity;
	for (auto& c : colliders) {
		//if (Collision::pointAB(
		//	center + (playerVel * player.getComponent<TransformComponent>().speed),
		//	c->getComponent<ColliderComponent>().ADD(player.getComponent<ColliderComponent>().collider)
		//	))
		//{
		//	//player.getComponent<TransformComponent>().position.x = c->getComponent<ColliderComponent>().collider.x;
		//	std::cout << " yippee\n";
		//}

		//SDL_FRect gary = c->getComponent<ColliderComponent>().ADD(player.getComponent<ColliderComponent>().collider);
		//if (Collision::pointAB(center+playerVel*player.getComponent<TransformComponent>().speed, gary)) {
		//	if (playerVel.x > 0) {
		//		player.getComponent<KeyboardController>().Stop(0, 0, 0, 1);
		//	}
		//	std::cout<<"fghj\n";
		//}
		if (Collision::AABB(c->getComponent<ColliderComponent>().collider, playerCol)) {
			
			//ss1 << gary.x << " x " << c->getComponent<ColliderComponent>().collider.x << " / "
			//<< gary.y << " y " << c->getComponent<ColliderComponent>().collider.y << " / "
			//<< gary.w << " w " << c->getComponent<ColliderComponent>().collider.w << " / "
			//<< gary.h << " h " << c->getComponent<ColliderComponent>().collider.h << " / ";

		   //player.getComponent<TransformComponent>().position = playerPos;
			auto tag = c->getComponent<ColliderComponent>().tag;
			if (tag == "wall") {
				player.getComponent<TransformComponent>().position = playerPos-playerOldVel;
			}
		   if (tag == "win") {
			   for (auto& c : colliders)
				   c->destroy();
			   map->LoadMap();
			   player.getComponent<TransformComponent>().position.Zero();
			   break;
		   }
		//}
		//else ss1 << "hmm";// player.getComponent<KeyboardController>().Stop(0, 0, 0, 0);

		}
	}
	for (auto& p : projectiles) {
		if (Collision::AABB(playerCol, p->getComponent<ColliderComponent>().collider)) {
			std::cout << "player hit\n";//p->destroy();
		}
	}

	label1.getComponent<UILabel>().SetLabelText(ss1.str(), "rob");

	camera.x = player.getComponent<TransformComponent>().position.x - 480.f ;
	camera.y = player.getComponent<TransformComponent>().position.y - 270.f ;

	
}
void Game::render() {
	int i=0;
	SDL_RenderClear(renderer);
	//тут будем добавлять штуки на рендер в порядке наслаивания
	for (auto& t : tiles) {
		t->draw();
		//std::cout << "Draw complete" << "\n";
	}
	for (auto& c : colliders) {
		if(c->getComponent<ColliderComponent>().tag=="wall")c->draw();
		if (c->getComponent<ColliderComponent>().tag == "win")c->draw();
	}
	for (auto& p : players) {
		p->draw();
	}
	for (auto& p : projectiles) {
		p->draw();
	}
	label.draw();
	label1.draw();
	SDL_RenderPresent(renderer);
}
//Очистка памяти
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}

