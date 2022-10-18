#ifndef CAMERA_H
#define CAMERA_H

#include "Point.h"

class Camera//tạo ra một khung camera hình chữ nhật, target vào nhân vật, khi nhân vật di chuyển khung camera cũng di chuyển và mọi thứ ở trong không gian đó sẽ được render còn bên ngoài thì không
{
private:
	Point* mTarget;//chọn mục tiêu là tâm của nhân vật
	Vector2D mPosition;
	SDL_Rect mViewBox;//phạm vi camera(hình chữ nhật)
	static Camera* sInstance;
	int	mSceneWidth, mSceneHeight;
public:

	Camera();

	void Update(float dt);


	inline int GetSceneWidth();
	inline int GetSceneWitdh();

	inline SDL_Rect GetViewBox();
	inline Vector2D GetPosition();

	inline void MoveX(float x);
	inline void MoveY(float y);

	inline void SetTarger(Point* target);
	inline void SetSceneLimit(int w, int h);

	inline static Camera* GetInstance();
};

#endif