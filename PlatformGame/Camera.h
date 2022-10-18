#ifndef CAMERA_H
#define CAMERA_H

#include "Point.h"

class Camera//tạo ra một khung camera hình chữ nhật, target vào nhân vật, khi nhân vật di chuyển khung camera cũng di chuyển và mọi thứ ở trong không gian đó sẽ được render còn bên ngoài thì không
{
private:
	Point* mTarget;//chọn mục tiêu là tâm của nhân vật
	Vector2D mPosition;
	SDL_FRect mViewBox;//phạm vi camera(hình chữ nhật)
	static Camera* sInstance;
	int	mSceneWidth, mSceneHeight;
public:

	Camera();

	void Update(float dt);


	 int GetSceneWidth();
	 int GetSceneWitdh();

	 SDL_FRect GetViewBox();
	 Vector2D GetPosition();

	 void MoveX(float x);
	 void MoveY(float y);

	 void SetTarger(Point* target);
	 void SetSceneLimit(int w, int h);

	 static Camera* getInstance();
};

#endif