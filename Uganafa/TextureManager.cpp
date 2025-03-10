#include "TextureManager.h"
#include <iostream>
//�������� �������
SDL_Texture* TextureManager::LoadTexture(const char* texture) {
	SDL_Surface* tmpSurface = IMG_Load(texture);
	SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	return tex;
}
//�������� ����� �������� � ��� ����� � ����
void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_FRect dest, SDL_RendererFlip flip)
{
	SDL_RenderCopyExF(Game::renderer, tex, &src, &dest,NULL,NULL,flip);
}
void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, NULL, NULL, flip);
}