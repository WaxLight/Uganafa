#pragma once
#include <SDL.h>
#include <SDL_image.h>
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

private:
	bool isRunning=false;
	SDL_Window* window;
};