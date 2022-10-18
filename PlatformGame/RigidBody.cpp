#include "stdafx.h"
#include "RigidBody.h"

RigidBody::RigidBody()
{
	fMass = UNI_MASS;
	fGravity = GRAVITY;
}

void RigidBody::setMass(float mass)
{
	fMass = mass;
}

void RigidBody::setGravity(float gravity)
{
	fGravity = fGravity;
}

void RigidBody::ApplyForce(Vector2D F)
{
	mForce = F;
}

void RigidBody::ApplyForceX(float Fx)
{
	mForce.setX(Fx);
}

void RigidBody::ApplyForceY(float Fy)
{
	mForce.setY(Fy);
}

void RigidBody::UnsetForce()
{
	mForce = Vector2D(0, 0);
}

void RigidBody::ApplyFriction(Vector2D Fr)
{
	mFriction = Fr;
}

void RigidBody::UnsetFriction()
{
	mFriction = Vector2D(0, 0);
}

float RigidBody::getMass()
{
	return fMass;
}

Vector2D RigidBody::getPosition()
{
	return mPosition;
}

Vector2D RigidBody::getVeclocity()
{
	return mVelocity;
}

Vector2D RigidBody::getAccleration()
{
	return mAccleration;
}
void RigidBody::Update(float dt)
{
	//Fr + F = m*a
	mAccleration.setX((mForce.getX() + mFriction.getX()) / fMass);//gia tốc trên bề mặt ngang
	mAccleration.setY(fGravity + mForce.getY() / fMass);//gia tốc trên trục dọc(nhảy), tác dụng lực bằng cách nhập từ bàn phím để nhảy và trọng lực(Gravity) sẽ kéo Object lại do khối lượng (Mass)
	mVelocity = mAccleration * dt;
	mPosition = mVelocity * dt;
}