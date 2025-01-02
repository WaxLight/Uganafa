#pragma once
#include <SDL.h>
#include <SDL_image.h>

class RenderWindow {
public:

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};