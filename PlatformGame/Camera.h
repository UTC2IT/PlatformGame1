#ifndef CAMERA_H
#define CAMERA_H

#include "Point.h"

class Camera//tạo ra một khung camera hình chữ nhật, target vào nhân vật, khi nhân vật di chuyển khung camera cũng di chuyển và mọi thứ ở trong không gian đó sẽ được render còn bên ngoài thì không
{
public:

	void Update(float dt);


	inline int GetSceneWidth() { return m_SceneWidth; }
	inline int GetSceneWitdh() { return m_SceneHeight; }

	inline SDL_Rect GetViewBox() { return m_ViewBox; }
	inline Vector2D GetPosition() { return m_Position; }

	inline void MoveX(float x) { m_Position.SetX(x); }
	inline void MoveY(float y) { m_Position.SetY(y); }

	inline void SetTarger(Point* target) { m_Target = target; }
	inline void SetSceneLimit(int w, int h) { m_SceneWidth = w; m_SceneHeight = h; }

	inline static Camera* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Camera(); }

private:

	Camera() : m_Target(nullptr), m_Position({}), m_ViewBox({})
	{
		m_ViewBox = { 0, 0, 900, 600 };//phạm vi hoạt động của camera(hình chữ nhật), có thể thay đổi thông số để phù hợp với Game
	}
	Point* m_Target;//chọn mục tiêu là tâm của nhân vật
	Vector2D m_Position;
	SDL_Rect m_ViewBox;//phạm vi camera(hình chữ nhật)
	static Camera* s_Instance;
	int	m_SceneWidth, m_SceneHeight;
};

#endif