#include "stdafx.h"
#include "Collision.h"

Collision* Collision::sInstance = nullptr;

Collision::Collision()
{
	//mCollisionLayer = Game::getInstance()->GetMap()->GetMapLayers()[0];//lấy layer phía dưới(layer của các vật cản)
	mCollisionTileMap = mCollisionLayer->getTileMap();
	mCollider = new Collider();
}
bool Collision::PointVsRect(Vector2D& const point, const SDL_Rect& rect)//không thể đặt const Vector2D  vì không tương thích với hàm thành viên, đói với SDL_Rect bên trong nó chỉ chứa các chỉ số để vẽ retangle
{
	return(point.getX() >= rect.x && point.getY() >= rect.w && point.getX() < rect.x + rect.w && point.getY() < rect.y + rect.h);
}
bool Collision::RectVsRect(const SDL_Rect& rect1, const SDL_Rect& rect2)
{
	bool x_overlaps = ((rect1.x <= rect2.x + rect2.w) && (rect1.x + rect1.w >= rect2.x));//check có sự chồng chéo lên nhau giữa 2tile với nhau trên trục x hay không
	bool y_overlaps = ((rect1.y <= rect2.y + rect2.h) && (rect1.y + rect1.h >= rect2.y));//check có sự chồng chéo lên nhau giữa 2tile với nhau trên trục y hay không
	return (x_overlaps && y_overlaps);
}

bool Collision::RayVsRect(const Vector2D& ray_origin, const Vector2D& ray_direction, const SDL_Rect& target, Vector2D& contact_point, Vector2D& contact_normal, float& t_hit_near)
{
	Vector2D t_near, t_far;
	t_near.X = (target.x - ray_origin.X) / ray_direction.X;
	t_near.Y = (target.y - ray_origin.Y) / ray_direction.Y;
	t_far.X = (target.x + target.w - ray_origin.X) / ray_direction.X;
	t_far.Y = (target.y + target.h - ray_origin.Y) / ray_direction.Y;

	if (t_near.X > t_far.X) { std::swap(t_near.X, t_far.X); }
	if (t_near.Y > t_far.Y) { std::swap(t_near.Y, t_far.Y); }

	if (t_near.X > t_far.Y || t_near.Y > t_far.X) return false;

	t_hit_near = std::max(t_near.X, t_near.Y);
	float t_hit_far = std::min(t_far.X, t_far.Y);

	if (t_hit_far < 0) return false;//hướng vector bị hướng ra phía ngược lại

	contact_point.X = ray_origin.X + t_hit_near * ray_direction.X;
	contact_point.Y = ray_origin.Y + t_hit_near * ray_direction.Y;

	if (t_near.X > t_near.Y)
	{
		if (ray_direction.X < 0)
		{
			contact_normal.X = 1;
			contact_normal.Y = 0;
		}
		else
		{
			contact_normal.X = -1;
			contact_normal.Y = 0;
		}
	}
	if (t_near.X < t_near.Y)
	{
		if (ray_direction.Y < 0)
		{
			contact_normal.X = 0;
			contact_normal.Y = 1;
		}
		else {
			contact_normal.X = 0;
			contact_normal.Y = -1;
		}
	}

	return true;
}

bool Collision::DynamicRectVsRect(const SDL_Rect& in, const SDL_Rect& target, const Vector2D& velocity, Vector2D contact_point, Vector2D& contact_normal, float& t_hit_near)
{
	if (velocity.X == 0 && velocity.Y == 0) return false;

	SDL_Rect expanded_target{};
	expanded_target.x = target.x - in.w / 2;
	expanded_target.y = target.y - in.h / 2;
	expanded_target.w = target.w + in.w;
	expanded_target.h = target.h + in.h;

	Vector2D origin;
	origin.X = in.x + in.w / 2;
	origin.Y = in.y + in.h / 2;

	if (RayVsRect(origin, velocity, expanded_target, contact_point, contact_normal, t_hit_near)) {
		if (t_hit_near >= 0.0f && t_hit_near <= 1.0f)
		{
			return true;
		}
		else return false;
	}
}

bool Collision::DynamicRectVsMap(const SDL_Rect& in, const SDL_Rect& rect_static, const Vector2D& velocity)
{
	Vector2D contact_point, contact_normal;
	float contact_time = 0.0f;

	if (DynamicRectVsRect(in, rect_static, velocity, contact_point, contact_normal, contact_time))
	{
		return true;
	}

	return false;
}

bool Collision::SortGridMap(const SDL_Rect& in, std::vector<SDL_Rect> gridmap, const Vector2D& velocity, Vector2D contact_point, Vector2D& contact_normal, float& t_hit_near)
{

	std::vector<std::pair<int, float>> ContactTimeOfRect;

	for (unsigned int i = 0; i < gridmap.size(); i++)
	{
		if (DynamicRectVsRect(in, gridmap[i], velocity, contact_point, contact_normal, t_hit_near))
		{
			ContactTimeOfRect.push_back({ i,t_hit_near });
		}
	}

	std::sort(ContactTimeOfRect.begin(), ContactTimeOfRect.end(), [](const std::pair<int, float>& a, const std::pair<int, float>& b)
		{
			return a.second < b.second;
		});

	for (auto j : ContactTimeOfRect)
	{
		if (DynamicRectVsRect(in, gridmap[j.first], velocity, contact_point, contact_normal, t_hit_near))
		{
			return true;
		}
	}
	return false;
}