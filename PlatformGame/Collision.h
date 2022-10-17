#ifndef COLLISION_H
#define COLLISION_H

#include "TileLayer.h"
#include "Collider.h"
#include "Game.h"

class Collision
{
private:
	Collision();

	Collider* m_Collider;

	TileMap m_CollisionTileMap;
	TileLayer* m_CollisionLayer;

	static Collision* s_Instance;
public:


	bool PointVsRect(Vector2D& point, const SDL_Rect& rect);
	bool RectVsRect(const SDL_Rect& rect1, const SDL_Rect& rect2);
	bool RayVsRect(const Vector2D& ray_origin, const Vector2D& ray_direction, const SDL_Rect& target, Vector2D& contact_point, Vector2D& contact_normal, float& t_hit_near);
	bool DynamicRectVsRect(const SDL_Rect& in, const SDL_Rect& target, const Vector2D& velocity, Vector2D contact_point, Vector2D& contact_normal, float& t_hit_near);
	bool DynamicRectVsMap(const SDL_Rect& in, const SDL_Rect& rect_static, const Vector2D& velocity);
	bool SortGridMap(const SDL_Rect& in, std::vector<SDL_Rect>gridmap, const Vector2D& velocity, Vector2D contact_point, Vector2D& contact_normal, float& t_hit_near);

	inline static Collision* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Collision(); }


};


#endif
