#pragma once
#include <SDL.h>
#include"Vector2D.h"

class ColliderComponent;

class Collision {
public:
	static bool AABB(const SDL_FRect& recA, const SDL_FRect& recB);//Access Alingh Binding Box
	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
	static bool pointAB(const Vector2D& p, const SDL_FRect& rec);
	static bool pointpointAB(const Vector2D& p1, const Vector2D& p2, const SDL_FRect& rec);
};