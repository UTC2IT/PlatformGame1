#ifndef IOBJECT_H
#define IOBJECT_H

#include "Game.h"
#include "Transform.h"
#include "Time.h"
#include "Camera.h"
#include "Collider.h"
#include "RigidBody.h"
#include "TileLayer.h"
#include "Collision.h"
#include "SpriteAnimation.h"
#include "ColSpriteAnimation.h"
#include "CollisionHandler.h"
class IObject//abstract class và interface là nền móng cho các class con khác phát triển thêm từ các hàm đã có sẵn trong abstract và interface
{
public:
	virtual ~IObject() {};
	virtual void Draw() = 0;
	virtual void Update(float dt) = 0;
	virtual void Clean() = 0;
private:

};

#endif