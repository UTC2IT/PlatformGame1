#include "stdafx.h"
#include "Enemy.h"
static Registrar<Enemy>	registrar("Zombie");


Enemy::Enemy(Properties* props) : Entity(props)
{

	mCollisionLayer = Game::getInstance()->getMap()->getMapLayers().back();//lấy layer phía dưới(layer của các vật cản)
	mCollisionTileMap = mCollisionLayer->getTileMap();

	mCollider = new Collider();
	mCollider->setBuffer(-20, -15, 35, 30);//điều chỉnh hit box nhân vật 

	mAttackedTime = ATTACKED_TIME;

	mRigidBody = new RigidBody();
	mRigidBody->setGravity(4.5f);

	mAnimation = new SpriteAnimation(false);
}

void Enemy::Draw()
{

	mAnimation->Draw(mTransform->getX(), mTransform->getY(), mWidth, mHeight, mFlip);

	//SDL_RenderDrawRect(Game::getInstance()->GetRenderer(), &m_EnemyHitBox);
	SDL_RenderDrawRectF(Game::getInstance()->getRenderer(), &mPlayerHitBox);

	SDL_SetRenderDrawColor(Game::getInstance()->getRenderer(), 255, 0, 0, 255);
	SDL_RenderFillRectF(Game::getInstance()->getRenderer(), &mHPBar);
	SDL_RenderDrawRectF(Game::getInstance()->getRenderer(), &mPlayerAttackRanger);
	//SDL_RenderDrawRect(Game::getInstance()->GetRenderer(), &m_SkillHitBox);
	//SDL_RenderDrawRect(Game::getInstance()->GetRenderer(), &m_HitBoxAttack);
	//SDL_RenderDrawRect(Game::getInstance()->GetRenderer(), &m_RangerActive);
}

void Enemy::Clean()
{
	delete mCollisionLayer;
	delete mRigidBody;
	delete mAnimation;
}
Enemy::~Enemy()
{
	std::cout << "deleded Enemy!" << std::endl;
}
void Enemy::setIsAttacked(bool isattacked, int damage)
{
	 mIsAttacked = isattacked; mDamageTaked = damage; 
}
void Enemy::setDirectionAttacked(int derection)
{
	mDirectionAttacked = derection;
}
void Enemy::Update(float dt)
{
	mIsRunning = false;
	mRigidBody->UnsetForce();

	Vector2D cam = Camera::getInstance()->getPosition();
	//cài đặt debug hitbox 
	mCollider->setBox(mTransform->getX(), mTransform->getY(), 64, 64);
	mHitBoxAttack = { 0,0,0,0 };
	//debug hit box vs camera
	mEnemyHitBox = mCollider->getBox();
	mEnemyHitBox.x -= cam.getX();
	mEnemyHitBox.y -= cam.getY();

	//debug attack ranger vs camera
	mPlayerAttackRanger = Game::getInstance()->getGameObjects().front()->getCollider()->getTileSetBox2();
	mPlayerAttackRanger.x -= cam.getX();
	mPlayerAttackRanger.y -= cam.getY();

	//lấy player debug hitbox
	mPlayerHitBox = Game::getInstance()->getGameObjects().front()->getCollider()->getBox();
	mPlayerHitBox.x -= cam.getX();
	mPlayerHitBox.y -= cam.getY();
	//lấy hitboxskill debug



	//checkerbox attack ranger 

	if (mFlip == SDL_FLIP_NONE)
		mCheckAttackRanger = { mEnemyHitBox.x ,mEnemyHitBox.y , mEnemyHitBox.w + 10, mEnemyHitBox.h };
	else
		mCheckAttackRanger = { mEnemyHitBox.x - 15,mEnemyHitBox.y, mEnemyHitBox.w + 10, mEnemyHitBox.h };

	//thanh HP
	mHPBar = { mEnemyHitBox.x, mEnemyHitBox.y - 10,static_cast<float>(mMaxHealthPoint) / 4,5 };

	//Vùng hoạt động của enemies
	mRangerActive = { mEnemyHitBox.x - BUFFER_ACTIVE_X,mEnemyHitBox.y - BUFFER_ACTIVE_Y,
					   mEnemyHitBox.w + BUFFER_ACTIVE_X * 2,mEnemyHitBox.h + BUFFER_ACTIVE_Y };


	//AI di chuyển cơ bản
	if (mIsActive && (mEnemyHitBox.x + mEnemyHitBox.w) < mPlayerHitBox.x && !mIsDeath)
	{
		mRigidBody->ApplyForceX(FORWARD * (RUN_FORCE * 0.5));
		Game::getInstance()->getGameObjects().front()->setDirectionAttacked(FORWARD);
		mFlip = SDL_FLIP_NONE;
		mIsRunning = true;
	}
	if (mIsActive && (mPlayerHitBox.x + mPlayerHitBox.w) < mEnemyHitBox.x && !mIsDeath)
	{
		mRigidBody->ApplyForceX(BACKWARD * (RUN_FORCE * 0.5));
		Game::getInstance()->getGameObjects().front()->setDirectionAttacked(BACKWARD);
		mFlip = SDL_FLIP_HORIZONTAL;
		mIsRunning = true;
	}
	if (mRigidBody->mVelocity.getY() > 0 && !mIsGrounded)
	{
		mIsFalling = true;
		mIsAttacking = false;
	}
	else
		mIsFalling = false;



	if (mIsAttacking && mAttackTime > 0)
	{
		mAttackTime -= dt;
	}
	else
	{
		mIsAttacking = false;
		mAttackTime = ATTACK_TIME;
	}

	if (mMaxHealthPoint == 0)
	{
		mIsDeath = true;
	}

	//tương tác
	Vector2D cp, cn;
	float t_hit_near;

	mCollisionLayer->getColCount();

	/*int tileSize = 16;
	int RowCount = 20;
	int ColCount = 60;*/

	int ColCount = mCollisionLayer->getColCount();
	int RowCount = mCollisionLayer->getRowCount();
	int tileSize = mCollisionLayer->getTilesize();

	int left_tile = (mCollider->getBox().x / tileSize);
	int right_tile = (mCollider->getBox().x + mCollider->getBox().w) / tileSize;

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
			}

		}
	}
	//tương tác enemy vs map 
	if (Collision::getInstance()->DynamicRectVsRect(mCollider->getBox(), mCollider->getTileSetBox1(), mRigidBody->getVeclocity(), cp, cn, t_hit_near))
	{
		mRigidBody->mVelocity += cn * Vector2D(std::abs(mRigidBody->mVelocity.getX()), std::abs(mRigidBody->mVelocity.getY())) * (1 - t_hit_near);
		mIsGrounded = true;
	}
	else
	{
		mIsGrounded = false;
	}

	//phát hiện player trong ranger attack 
	if (Collision::getInstance()->RectVsRect(mPlayerAttackRanger, mEnemyHitBox) ||
		Collision::getInstance()->RectVsRect(mSkillHitBox, mEnemyHitBox))
	{
		mIsAttacked = true;
	}
	else
	{
		mIsAttacked = false;
	}

	if (Collision::getInstance()->RectVsRect(mPlayerHitBox, mCheckAttackRanger) && !mIsDeath && !mIsAttacked)
	{
		mRigidBody->UnsetForce();
		mIsAttacking = true;

	}
	else
	{
		mIsAttacking = false;
	}



	if (Collision::getInstance()->RectVsRect(mPlayerHitBox, mRangerActive))
	{
		mIsActive = true;
	}
	else
	{
		mIsActive = false;
	}


	//tương tác enemy vs attack ranger


	//phát hiện player trong ranger 


	//khoảng cách thay đổi
	mRigidBody->mPosition.setX(mRigidBody->mVelocity.getX()* dt);
	mRigidBody->mPosition.setY(mRigidBody->mVelocity.getY()* dt);
	//update khoảng cách thay đổi vào vị trí hiện tại
	mTransform->translatex(mRigidBody->getPosition().getX());
	mTransform->translatey(mRigidBody->getPosition().getY());

	//cập nhật trạng thái
	mRigidBody->Update(dt);
	IsAttack();
	AnimationState();
	mAnimation->Update(dt);

}
Collider* Enemy::getCollider()
{
	return mCollider;
}
bool Enemy::CheckLastAnimation()
{

	if (mAnimation->getTextureID() == "Zombie_Die")//thực hiện effect die trước khi xóa 
	{
		if (mAnimation->getCurrFrame() == mAnimation->getFrameCount() - 1)//kiểm tra khi chaỵ đến frame cuối của Zombie_Die.png thì xóa object
		{
			return true;
		}
	}
	return false;
}

void Enemy::IsAttack()
{
	if (mAnimation->getTextureID() == "Zombie_Attack")//thực hiện effect die trước khi xóa 
	{
		if (mAnimation->getCurrFrame() == 5 || mAnimation->getCurrFrame() == 9)//kiểm tra khi chaỵ đến frame cuối của Zombie_Die.png thì xóa object
		{
			if (mFlip == SDL_FLIP_NONE)
			{
				mHitBoxAttack = { mEnemyHitBox.x ,mEnemyHitBox.y , mEnemyHitBox.w + 10, mEnemyHitBox.h };
			}
			else
				mHitBoxAttack = { mEnemyHitBox.x - 15,mEnemyHitBox.y, mEnemyHitBox.w + 10, mEnemyHitBox.h };
		}
		else
			mHitBoxAttack = { 0,0,0,0 };
		if (Collision::getInstance()->RectVsRect(mHitBoxAttack, mPlayerHitBox) && !mIsDeath && !mIsAttacked)
		{
			Game::getInstance()->getGameObjects().front()->setIsAttacked(true, mDamage);
		}
		else
		{
			Game::getInstance()->getGameObjects().front()->setIsAttacked(false, mDamage);
		}
	}

}

void Enemy::AnimationState()
{

	mAnimation->setProps("Zombie_Idle", 0, 4, 120);


	if (mIsAttacked)
	{
		mAnimation->setProps("Zombie_Hurt", 0, 3, 120);
		if (mMaxHealthPoint > 0)
		{
			mMaxHealthPoint -= 2;
		}
	}
	if (mIsDeath)
	{
		mAnimation->setProps("Zombie_Die", 0, 13, 120);
	}
	if (mIsRunning && !mIsDeath)
	{
		mAnimation->setProps("Zombie_Run", 0, 12, 120);
		//m_Animation->Triggered()
	}
	if (mIsAttacking)
	{
		mAnimation->setProps("Zombie_Attack", 0, 13, 150);
	}
}