#include "Mage.h"
#include "Mage.h"
#include "RigidBody.h"
#include "Camera.h"


static Registrar<Mage> registrar("Player");


Mage::Mage(Properties* props) : Entity(props)
{

	mCollisionLayer = Game::getInstance()->getMap()->getMapLayers()[1];//lấy layer phía dưới(layer của các vật cản)
	mCollisionTileMap = mCollisionLayer->getTileMap();
	Vector2D cam = Camera::getInstance()->getPosition();


	mCollisionLayer1 = Game::getInstance()->getMap()->getMapLayers()[0];
	mCollisionTileMap1 = mCollisionLayer1->getTileMap();


	mStatus.health = PLAYER_MAX_HEALTH;
	mCollisionLayer1->RgidMap();
	mRgidMap = mCollisionLayer1->getCollisionRect();
	mFlip = SDL_FLIP_NONE;
	mAttackTime = ATTACK_TIME;

	mJumpTime = JUMP_TIME;
	mJumpForce = JUMP_FORCE;

	mCollider = new Collider();
	mCollider->setBuffer(-18, -17, 30, 20);//điều chỉnh hit box nhân vật 


	mRigidBody = new RigidBody();
	mRigidBody->setGravity(4.5f);


	mSpriteAnimation = new ColSpriteAnimation(false);
	mAnimation = new SpriteAnimation(false);

}
void Mage::Draw()
{
	Vector2D cam = Camera::getInstance()->getPosition();
	mSpriteAnimation->DrawCol(mTransform->getX(), mTransform->getY(), mWidth, mHeight, mFlip, 1.25, 1.25);

	SDL_FRect hitbox = mCollider->getBox();

	SDL_SetRenderDrawColor(Game::getInstance()->getRenderer(), 254, 0, 0, 255);
	SDL_RenderFillRectF(Game::getInstance()->getRenderer(), &mHPBar);
	//SDL_RenderFillRect(Game::getInstance()->getRenderer(), &hitbox);


	/*SDL_RenderDrawRect(Game::getInstance()->getRenderer(), &check);
	SDL_FRect box = m_Collider->getBox();
	box.x -= cam.getX();
	box.y -= cam.getY();

	SDL_FRect collsion = m_Collider->getTilesetBox1();
	collsion.x -= cam.getX();
	collsion.y -= cam.getY();

	SDL_FRect attack = m_Collider->getTilesetBox2();
	attack.x -= cam.getX();
	attack.y -= cam.getY();
	SDL_RenderDrawRect(Game::getInstance()->getRenderer(), &box);
	SDL_RenderDrawRect(Game::getInstance()->getRenderer(), &collsion);
	SDL_RenderDrawRect(Game::getInstance()->getRenderer(), &attack);*/



}

void Mage::Update(float dt)
{
	mCollider->setBox(mTransform->getX(), mTransform->getY(), 48, 54);
	mIsStop = false;
	mIsCrouch = false;
	mIsRunning = false;//nếu không đưa về false nhân vật sẽ ở mãi một trạng thái
	mIsCrouching = false;


	mRigidBody->UnsetForce();

	Vector2D cam = Camera::getInstance()->getPosition();



	SDL_FRect targetss1 = mCollider->getTileSetBox1();

	targetss1.x -= cam.getX();
	targetss1.y -= cam.getY();

	//SDL_RenderDrawRect(Game::getInstance()->getRenderer(), &targetss1);

	mAttackRanger = mCollider->getTileSetBox2();

	mAttackRanger.x -= cam.getX();
	mAttackRanger.y -= cam.getY();
	Vector2D cp, cn;
	float t_hit_near;

	mHPBar = { 0,0,static_cast<float>(mStatus.health), 10 };
	if (mStatus.health < 100)
	{
		mStatus.health += dt * 0.01;
	}



	if (Inputs::getInstance()->getAxisKey(HORIZONTAl) == FORWARD && !mIsAttacking && !mIsAttacked)
	{
		mRigidBody->ApplyForceX(FORWARD * RUN_FORCE);
		mFlip = SDL_FLIP_NONE;
		mIsRunning = true;
	}


	if (Inputs::getInstance()->getAxisKey(HORIZONTAl) == BACKWARD && !mIsAttacking && !mIsAttacked)
	{
		mRigidBody->ApplyForceX(BACKWARD * RUN_FORCE);
		mFlip = SDL_FLIP_HORIZONTAL;
		mIsRunning = true;
	}



	if (Inputs::getInstance()->getKeyDown(SDL_SCANCODE_S))
	{
		mRigidBody->UnsetForce();
		mIsCrouch = true;
	}
	else
	{
		mCrouchingLastFrame = false;
	}
	if (Inputs::getInstance()->getKeyDown(SDL_SCANCODE_J) && mIsCrouch)
	{
		mRigidBody->UnsetForce();
		mCrouchAttackTime -= dt;
		mIsCrouchAttacking = true;
	}
	else
	{
		mIsCrouchAttacking = false;
		mCrouchAttackTime = CROUCH_ATTACK_TIME;
	}

	if (Inputs::getInstance()->getKeyDown(SDL_SCANCODE_J))
	{
		mRigidBody->UnsetForce();
		mIsAttacking = true;
	}

	if (Inputs::getInstance()->getKeyDown(SDL_SCANCODE_K) && mIsGrounded)
	{
		mIsJumping = true;
		mIsGrounded = false;
		mRigidBody->ApplyForceY(UPWARD * mJumpForce);
	}
	if (Inputs::getInstance()->getKeyDown(SDL_SCANCODE_K) && mIsJumping && mJumpTime > 0) {
		mJumpTime -= dt;
		mRigidBody->ApplyForceY(UPWARD * mJumpForce);
	}
	else {
		mIsJumping = false;
		mJumpTime = JUMP_TIME;
	}
	if (Inputs::getInstance()->getKeyDown(SDL_SCANCODE_U))
	{
		mIsSkilling = true;
	}


	if (mRigidBody->mVelocity.getY() > 0 && !mIsGrounded)
	{
		mIsFalling = true;
	}
	else
		mIsFalling = false;




	if (mIsAttacked)
	{
		mRigidBody->UnsetForce();
		if (mDirectionAttacked == FORWARD)
		{
			mRigidBody->ApplyForceX(FORWARD * RUN_FORCE * 0.2);
		}
		else
		{
			mRigidBody->ApplyForceX(BACKWARD * RUN_FORCE * 0.2);
		}
	}




	if (mIsAttacking && mAttackTime > 0)
	{
		IsAttack();
		mAttackTime -= dt;
	}
	else
	{
		mIsAttacking = false;
		mAttackTime = ATTACK_TIME;
		mCollider->setTileSetBox2(0, 0, 0, 0);
	}

	if (mIsSkilling)
	{
		IsSkillCast();
	}
	else
	{
		mIsSkilling = false;

	}

	if (mStatus.health == 0)
	{
		mIsDeath = true;
		mRigidBody->UnsetForce();
	}
	else
	{
		mIsDeath = false;
	}
	int ColCount = mCollisionLayer->getColCount();
	int RowCount = mCollisionLayer->getRowCount();
	int tileSize = mCollisionLayer->getTilesize();

	int left_tile = (mCollider->getBox().x / tileSize);
	int right_tile = (mCollider->getBox().x + mCollider->getBox().w + 10) / tileSize;

	int top_tile = (mCollider->getBox().y / tileSize);
	int bottom_tile = (mCollider->getBox().y + mCollider->getBox().h + 20) / tileSize;

	if (left_tile < 0) left_tile = 0;
	if (right_tile > ColCount) right_tile = ColCount;

	if (top_tile < 0) top_tile = 0;
	if (bottom_tile > RowCount) bottom_tile = RowCount;

	for (int i = left_tile; i < right_tile; ++i)
	{
		for (int j = top_tile; j < bottom_tile; ++j)
		{
			if ((mCollisionTileMap[j][i] >= 49 && mCollisionTileMap[j][i] <= 54))
			{
				mCollider->setTileSetBox1(i * 16, j * 16, 16, 16);
				if (mRigidBody->mVelocity.getY() > 0 && !mIsGrounded)
				{
					mIsFalling = false;
					mIsLanding = true;
				}
			}
			else
			{
				mIsLanding = false;
			}

		}
	}
	if (Collision::getInstance()->DynamicRectVsRect(mCollider->getBox(), mCollider->getTilesetBox1(), mRigidBody->getVeclocity(), cp, cn, t_hit_near))
	{

		mRigidBody->mVelocity += cn * Vector2D(std::abs(mRigidBody->mVelocity.getX()), std::abs(mRigidBody->mVelocity.getY())) * (1 - t_hit_near);
		mIsGrounded = true;
		mFallingLastFrame = false;
		mIsLanding = false;
	}
	else
	{
		mIsGrounded = false;
	}

	if (Collision::getInstance()->SortGridMap(mCollider->getBox(), mRgidMap, mRigidBody->getVeclocity(), cp, cn, t_hit_near))
	{

		mRigidBody->mVelocity += cn * Vector2D(std::abs(mRigidBody->mVelocity.getX()), std::abs(mRigidBody->mVelocity.getY())) * (1 - t_hit_near);
		mIsGrounded = true;
	}



	mRigidBody->mPosition.setX(mRigidBody->mVelocity.getX()* dt);
	mRigidBody->mPosition.setY(mRigidBody->mVelocity.getY()* dt);




	mTransform->translatex(mRigidBody->getPosition().getX());
	mTransform->translatey(mRigidBody->getPosition().getY());


	mOrigin->setX(mTransform->getX() + static_cast<float>(mWidth / 2));
	mOrigin->setY(mTransform->getY() + static_cast<float>(mHeight / 2));


	mRigidBody->Update(dt);
	AnimationState();
	mSpriteAnimation->Update(dt);

}


void Mage::IsAttack()
{
	if (mSpriteAnimation->getTextureID() == "Battlemage Attack 1")
	{
		if (mSpriteAnimation->getCurrFrame() == 4)
		{
			if (mFlip == SDL_FLIP_NONE)
			{
				mCollider->setTileSetBox2(mTransform->getX() - mCollider->getBuffer().x * 2
					, mTransform->getY() - mCollider->getBuffer().y
					, mCollider->getBox().w
					, mCollider->getBox().h);
			}
			else

				mCollider->setTileSetBox2(mTransform->getX()
					, mTransform->getY() - mCollider->getBuffer().y
					, mCollider->getBox().w
					, mCollider->getBox().h);

		}
		else
		{
			mCollider->setTileSetBox2(0, 0, 0, 0);
		}

	}
	if (mSpriteAnimation->getTextureID() == "Crouch Attack")
	{
		if (mSpriteAnimation->getCurrFrame() == 2)
		{
			if (mFlip == SDL_FLIP_NONE)
			{
				mCollider->setTileSetBox2(mTransform->getX() - mCollider->getBuffer().x * 2
					, mTransform->getY() - mCollider->getBuffer().y * 2
					, mCollider->getBox().w
					, mCollider->getBox().h / 2);
			}
			else
				mCollider->setTileSetBox2(mTransform->getX()
					, mTransform->getY() - mCollider->getBuffer().y * 2
					, mCollider->getBox().w
					, mCollider->getBox().h / 2);
		}
		else
		{
			mCollider->setTileSetBox2(0, 0, 0, 0);
		}
	}
}

void Mage::IsSkillCast()
{
	if (mSpriteAnimation->getTextureID() == "Thunderstrike w blur")
	{
		if (mSpriteAnimation->getCurrFrame() == 4)
		{

		}
	}
}
bool Mage::CheckLastAnimation()
{

	if (mSpriteAnimation->getTextureID() == "_DeathNoMovement")//thực hiện effect die trước khi xóa 
	{
		if (mSpriteAnimation->getCurrFrame() == mSpriteAnimation->getFrameCount() - 1)//kiểm tra khi chaỵ đến frame cuối của Zombie_Die.png thì xóa object
		{
			return true;
		}
	}

	return false;
}
inline Collider* Mage::getCollider()
{
	return mCollider;
}
void Mage::setIsAttacked(bool isattacked, int damage)
{
	mIsAttacked = isattacked; mDamageTaked = damage;
}
void Mage::setDirectionAttacked(int derection)
{
	mDirectionAttacked = derection;
}
void Mage::CheckLastAnimationState(std::string ID, bool& statechecker)
{
	if (mSpriteAnimation->getTextureID() == ID)//thực hiện effect die trước khi xóa 
	{
		if (mSpriteAnimation->getCurrFrame() == mSpriteAnimation->getFrameCount() - 1)//kiểm tra khi chaỵ đến frame cuối của Zombie_Die.png thì xóa object
		{
			statechecker = true;
			mSpriteAnimation->setCurrFrame(0);
		}
	}
}


void Mage::AnimationState()
{
	mSpriteAnimation->setPropsCol("Battlemage Idle", 0, 8, 80);

	if (mIsRunning)
	{
		mSpriteAnimation->setPropsCol("Battlemage Run", 0, 10, 80);
	}

	if (mIsCrouch)
	{
		mSpriteAnimation->setPropsCol("Battlemage Crouch", 0, 9, 80);
		CheckLastAnimationState("Battlemage Crouch", mCrouchingLastFrame);
	}


	if (mIsJumping)
	{
		mSpriteAnimation->setPropsCol("Jump Foward Going Up", 0, 2, 80);
	}


	if (mIsFalling)
	{
		mSpriteAnimation->setPropsCol("Jump Foward Going Down", 0, 5, 80);
		CheckLastAnimationState("Jump Foward Going Down", mFallingLastFrame);
	}
	if (mFallingLastFrame)
	{
		mSpriteAnimation->setPropsCol("Going Down 1Frame", 0, 2, 80);
	}
	if (mCrouchingLastFrame)
	{
		mSpriteAnimation->setPropsCol("Crouch 1Frame", 0, 1, 80);
	}

	if (mIsLanding)
	{
		mSpriteAnimation->setPropsCol("Jump Foward Grounded", 0, 4, 80);
	}

	if (mIsAttacking)
		mSpriteAnimation->setPropsCol("Battlemage Attack 1", 0, 8, 80);

	if (mIsAttacked)
	{
		if (mStatus.health > 0)
		{
			mStatus.health -= mDamageTaked;
		}
		mSpriteAnimation->setPropsCol("Hurt 1", 0, 2, 80);
	}
	if (mIsSkilling)
	{

		mAnimation->setProps("Thunderstrike w blur", 0, 13, 100);
	}


	if (mIsDeath)
	{
		mSpriteAnimation->setPropsCol("Battlemage Death", 0, 12, 80);
	}
	if (mIsCrouchAttacking)
	{
		mSpriteAnimation->setPropsCol("Crouch Attack", 0, 7, 80);
	}
	if (mIsStop)
	{
		mSpriteAnimation->setPropsCol("Battlemage Stop", 0, 5, 80);
	}



}

void Mage::Clean()
{
	delete mRigidBody;
	delete mSpriteAnimation;
	delete mCollisionLayer;
	//m_Skill->Clean();
}

