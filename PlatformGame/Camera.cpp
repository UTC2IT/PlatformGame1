#include "stdafx.h"
#include "Camera.h"


Camera* Camera::sInstance = nullptr;

Camera::Camera() : mTarget(nullptr), mPosition({}), mViewBox({})
{
	mViewBox = { 0, 0, 900, 600 };//phạm vi hoạt động của camera(hình chữ nhật), có thể thay đổi thông số để phù hợp với Game
}

void Camera::Update(float dt)
{
	if (mTarget != nullptr)
	{
		mViewBox.x = mTarget->getX() - 900 / 2;//Kiểm tra target x của nhân vật lệch khỏi giữa màn hình bao nhiêu đơn vị
		mViewBox.y = mTarget->getY() - 600 / 2;//Kiểm tra target y của nhân vật lệch khỏi giữa màn hình bao nhiêu đơn vị
		//std::cout << m_ViewBox.x << " " << m_ViewBox.y;
		if (mViewBox.x < 0)//trả về ViewBox.x = 0 nếu chưa đi quá nửa màn hình, vì nhân vật lui về thì m_Target->GetX() - SCREEN_WIDTH / 2 < 0, theo chiều ngang 
		{
			mViewBox.x = 0;
		}
		if (mViewBox.y < 0)//trả về ViewBox.y = 0 nếu chưa đi quá nửa màn hình, theo chiều dọc
		{
			mViewBox.y = 0;
		}
		if (mViewBox.x > (mSceneWidth - mViewBox.w))
		{
			mViewBox.x = (mSceneWidth - mViewBox.w);
		}
		if (mViewBox.y > (mSceneHeight - mViewBox.h))
		{
			mViewBox.y = (mSceneHeight - mViewBox.h);
		}

		//if (mViewBox.x > (2* SCREEN_WIDTH - mViewBox.w))//(2*SCREEN_WIDTH - mViewBox.w) -> giới hạn chiều rộng hoạt động của camera là 2*SCREEN_WIDTH tức là 1920, khi cạnh cuối của của camera(hình chữ nhật) đến điểm WIDTH = 1920 sẽ bị chặn
		//{
		//	mViewBox.x = (2 *SCREEN_WIDTH - mViewBox.w);
		//}
		//if (mViewBox.y > (2 * SCREEN_HEIGHT - mViewBox.h))//(2 * SCREEN_HEIGHT - mViewBox.h) tương tự với cách giải thích trên dùng để giới hạn chiều cao hoạt động của camera
		//{
		//	mViewBox.y = (2 * SCREEN_HEIGHT - mViewBox.h);
		//}

		mPosition = Vector2D(mViewBox.x, mViewBox.y);
		//khi lấy tọa độ hiện tại của nhân vật trừ cho m_ViewBox sau khi tính toán ta sẽ được tọa độ luôn ở giữa màn hình(trừ khi đến đã bị điểm giới hạn) vì vậy trình render sẽ luôn render nhân vật ở giữa màn hình
		//đối với map vì map không di chuyển như nhân vật nên khi trừ cho m_ViewBox map sẽ thoát khỏi không gian render của camera và không được render trong camera

	}
}

inline int Camera::GetSceneWidth()
{
	return mSceneWidth;
}

inline int Camera::GetSceneWitdh()
{
	mSceneHeight;
}

inline SDL_FRect Camera::GetViewBox()
{
	return mViewBox;
}

inline Vector2D Camera::GetPosition()
{
	return mPosition;
}

inline void Camera::MoveX(float x)
{
	mPosition.setX(x);
}

inline void Camera::MoveY(float y)
{
	mPosition.setY(y);
}

inline void Camera::SetTarger(Point* target)
{
	mTarget = target;
}

inline void Camera::SetSceneLimit(int w, int h)
{
	mSceneWidth = w; mSceneHeight = h;
}

inline Camera* Camera::getInstance()
{
	return sInstance = (sInstance != nullptr) ? sInstance : new Camera();
}
