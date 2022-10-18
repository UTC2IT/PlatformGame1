#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

#define ATTACKED_TIME 15
#define MAX_HEALTH_POINT 100

#define BUFFER_ACTIVE_X 125
#define BUFFER_ACTIVE_Y 30

#define ENEMY_DAMAGE 1
#define RUN_FORCE 3.0f
#define ATTACK_TIME 20.0f
class Enemy : public Entity
{
public:
	Enemy(Properties* props);

	virtual void Draw();
	virtual void Clean();
	virtual void Update(float dt);

	~Enemy();
	virtual void setIsAttacked(bool isattacked, int damage);
	virtual void setDirectionAttacked(int derection);

	virtual  Collider* getCollider();
	virtual bool CheckLastAnimation();

	void IsAttack();
	void AnimationState();
private:
	RigidBody* mRigidBody;
	SpriteAnimation* mAnimation;

	SDL_FRect mPlayerHitBox;
	SDL_FRect mEnemyHitBox;
	SDL_FRect mPlayerAttackRanger;
	SDL_FRect mHPBar;
	SDL_FRect mRangerActive;
	SDL_FRect mCheckAttackRanger;
	SDL_FRect mHitBoxAttack;
	SDL_FRect mSkillHitBox;

	bool mIsAttacking;
	bool mIsDeath;
	bool mIsAttacked;
	bool mIsActive;
	bool mIsRunning;
	bool mIsGrounded;
	bool mIsFalling;
	bool mDirectionAttacked;




	float mAttackedTime;

	unsigned int mMaxHealthPoint = MAX_HEALTH_POINT;

	Collider* mCollider;
	SDL_RendererFlip mFlip;

	int	mDamage = ENEMY_DAMAGE;
	int mRow = {}, mFrame = {}, mFrameCount = {};
	int mAnimSpeed = {};
	int mAttackTime;
	int mDamageTaked;

	TileMap mCollisionTileMap;
	TileLayer* mCollisionLayer;
};
#endif