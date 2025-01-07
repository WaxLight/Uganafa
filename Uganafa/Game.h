#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

class AssetManager;
class ColliderComponent;

class Game {
public:
	Game();
	~Game();
	void init(const char* p_title, int xpos, int ypos,int width,int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static bool isRunning;
	static SDL_FRect camera;
	static AssetManager* assets;

	enum groupLabels : std::size_t {
		groupMap,
		groupPlayers,
		groupEnemies,
		groupColliders,
		groupProjectiles
	};
private:
	SDL_Window* window;
};