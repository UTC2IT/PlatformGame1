#ifndef MAGE_H
#define MAGE_H

#include "stdafx.h"
#include "SpriteAnimation.h"
#include "ColSpriteAnimation.h"
#include "CollisionHandler.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Entity.h"
#include "Game.h"
#define JUMP_TIME 20.0f
#define JUMP_FORCE 15.0f

#define CROUCH_ATTACK_TIME 20.0f
#define ATTACK_TIME 20.0f
#define RUN_FORCE 3.0f

#define PLAYER_MAX_HEALTH 200.0f

struct Status
{
	float health;
	float mana;
	float heal;
};

class Mage : public Entity
{
public:

	Mage(Properties* props);


	virtual void Draw();
	virtual void Update(float dt);
	virtual void Clean();

	virtual bool CheckLastAnimation();
	virtual inline Collider* getCollider();

	virtual void setIsAttacked(bool isattacked, int damage);
	virtual void setDirectionAttacked(int derection);
	void CheckLastAnimationState(std::string ID, bool& statechecker);
	void AnimationState();
	void IsAttack();
	void IsSkillCast();

private:
	bool mIsJumping;// nếu đang nhảy sử dụng animation nhảy
	bool mIsGrounded;//nếu ở dưới đất sử dụng animation mặc định
	bool mIsRunning;
	bool mIsFalling;
	bool mIsAttacking;
	bool mIsCrouch;
	bool mIsAttacked;
	bool mDealDamage;
	bool mIsDeath;
	bool mIsCrouching;
	bool mIsCrouchAttacking;
	bool mIsStop;
	bool mIsLanding;//đáp đất
	bool mFallingLastFrame;
	bool mCrouchingLastFrame;
	bool mIsSkilling;
	bool mIsCasting;
	bool mSkillEnded;



	int mDamageTaked;
	Status mStatus;
	int mDirectionAttacked;
	float mCrouchAttackTime = CROUCH_ATTACK_TIME;

	float mJumpTime;//khoảng thời gian từ khi nhảy đến khi chạm đất
	float mJumpForce;//lực tác dụng để nhảy
	float mAttackTime;

	Collider* mCollider{};
	SDL_RendererFlip mFlip;

	SDL_FRect mHPBar;
	SDL_FRect mAttackRanger;
	SDL_FRect check;

	int mRow = {}, mFrame = {}, mFrameCount = {};
	int mAnimSpeed = {};

	ColSpriteAnimation* mSpriteAnimation = nullptr;
	SpriteAnimation* mAnimation = nullptr;
	RigidBody* mRigidBody = nullptr;


	TileMap mCollisionTileMap;
	TileMap mCollisionTileMap1;
	TileLayer* mCollisionLayer;
	TileLayer* mCollisionLayer1;
	std::vector<SDL_FRect> mRgidMap;
};

#endif