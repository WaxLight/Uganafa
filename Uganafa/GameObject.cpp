#include "GameObject.h"
#include "TextureManager.h"
//Загрузка текстуры игрового объекта в опр. месте
GameObject::GameObject(const char* texturesheet,int x, int y) {
	objTexture = TextureManager::LoadTexture(texturesheet);
	xpos = x;
	ypos = y;
}
//Обновление позиции объекта
void GameObject::Update(){
	

	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;
}
//Загрузка копии объекта 
void GameObject::Render() {
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}