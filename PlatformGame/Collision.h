#ifndef COLLISION_H
#define COLLISION_H

#include "TileLayer.h"
#include "Game.h"

class Collision
{
private:
	Collision();

	Collider* mCollider;

	TileMap mCollisionTileMap;
	TileLayer* mCollisionLayer;

	static Collision* sInstance;
public:


	bool PointVsRect(Vector2D& point, const SDL_FRect& rect);
	bool RectVsRect(const SDL_FRect& rect1, const SDL_FRect& rect2);
	bool RayVsRect(const Vector2D& ray_origin, const Vector2D& ray_direction, const SDL_FRect& target, Vector2D& contact_point, Vector2D& contact_normal, float& t_hit_near);
	bool DynamicRectVsRect(const SDL_FRect& in, const SDL_FRect& target, const Vector2D& velocity, Vector2D contact_point, Vector2D& contact_normal, float& t_hit_near);
	bool DynamicRectVsMap(const SDL_FRect& in, const SDL_FRect& rect_static, const Vector2D& velocity);
	bool SortGridMap(const SDL_FRect& in, std::vector<SDL_FRect>gridmap, const Vector2D& velocity, Vector2D contact_point, Vector2D& contact_normal, float& t_hit_near);

	inline static Collision* getInstance() { return sInstance = (sInstance != nullptr) ? sInstance : new Collision(); }


};


#endif
