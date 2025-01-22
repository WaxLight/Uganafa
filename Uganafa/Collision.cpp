#include "Collision.h"
#include "ECS/ColliderComponent.h"
bool Collision::AABB(const SDL_FRect& recA, const SDL_FRect& recB) {
	if (
		recA.x + recA.w >= recB.x &&
		recB.x + recB.w >= recA.x &&
		recA.y + recA.h >= recB.y &&
		recB.y + recB.h >= recA.y
		) return true;
	return false;
}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{
	if (AABB(colA.collider, colB.collider)) {
	//	std::cout << colA.tag << " hit " << colB.tag << std::endl;
		return true;
	}
	return false;
}

bool Collision::pointAB(const Vector2D& p, const SDL_FRect& rec) {
	if (
		p.x >= rec.x &&
		p.x <= rec.x + rec.w &&
		p.y >= rec.y &&
		p.y <= rec.y + rec.h
		) return true;
	return false;
}
bool Collision::pointpointAB(const Vector2D& p1,const Vector2D& p2, const SDL_FRect& rec) {
	if (
		/*p1.x >= rec.x &&
		p1.x <= rec.x + rec.w &&
		p1.y >= rec.y &&
		p1.y <= rec.y + rec.h*/
		p1.x<rec.x&&p2.x<rec.x||
		p1.x>=rec.x*rec.w&&p2.x>rec.x*rec.w||
		p1.y>rec.y&&p2.y>rec.y||
		p1.y<rec.y * rec.h &&p2.y<rec.y*rec.h
		) return true;
	return false;
}
