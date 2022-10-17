#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#define UNI_MASS 1.0f
#define GRAVITY 9.8f

#define	FORWARD 1
#define BACKWARD -1

#define	UPWARD -1
#define DOWNWARD 1

class RigidBody
{
private:
	friend class TileLayer;
	float fMass;//khối lượng
	float fGravity;//trọng lực
	Vector2D mForce;
	Vector2D mFriction;//ma sát khi đi trên đất,nuocs...
	Vector2D mPosition;//vị trí
	Vector2D mVelocity;//vận tốc
	Vector2D mAccleration;//gia tốc
public:
	RigidBody();
	void setMass(float mass);
	void setGravity(float gravity);
	void ApplyForce(Vector2D F);//Lực tác dụng
	void ApplyForceX(float Fx);//lực tác dụng lên trục ngang
	void ApplyForceY(float Fy);//lực tác dụng lên trục dọc
	void UnsetForce();
	void ApplyFriction(Vector2D Fr);
	void UnsetFriction();

	float getMass();
	Vector2D getPosition();
	Vector2D getVeclocity();
	Vector2D getAccleration();
	void Update(float dt);//datetime

};
#endif
