#include "stdafx.h"
#include "Camera.h"


Camera* Camera::s_Instance = nullptr;

void Camera::Update(float dt)
{
	if (m_Target != nullptr)
	{
		m_ViewBox.x = m_Target->GetX() - 900 / 2;//Kiểm tra target x của nhân vật lệch khỏi giữa màn hình bao nhiêu đơn vị
		m_ViewBox.y = m_Target->GetY() - 600 / 2;//Kiểm tra target y của nhân vật lệch khỏi giữa màn hình bao nhiêu đơn vị
		//std::cout << m_ViewBox.x << " " << m_ViewBox.y;
		if (m_ViewBox.x < 0)//trả về ViewBox.x = 0 nếu chưa đi quá nửa màn hình, vì nhân vật lui về thì m_Target->GetX() - SCREEN_WIDTH / 2 < 0, theo chiều ngang 
		{
			m_ViewBox.x = 0;
		}
		if (m_ViewBox.y < 0)//trả về ViewBox.y = 0 nếu chưa đi quá nửa màn hình, theo chiều dọc
		{
			m_ViewBox.y = 0;
		}
		if (m_ViewBox.x > (m_SceneWidth - m_ViewBox.w))
		{
			m_ViewBox.x = (m_SceneWidth - m_ViewBox.w);
		}
		if (m_ViewBox.y > (m_SceneHeight - m_ViewBox.h))
		{
			m_ViewBox.y = (m_SceneHeight - m_ViewBox.h);
		}

		//if (m_ViewBox.x > (2* SCREEN_WIDTH - m_ViewBox.w))//(2*SCREEN_WIDTH - m_ViewBox.w) -> giới hạn chiều rộng hoạt động của camera là 2*SCREEN_WIDTH tức là 1920, khi cạnh cuối của của camera(hình chữ nhật) đến điểm WIDTH = 1920 sẽ bị chặn
		//{
		//	m_ViewBox.x = (2 *SCREEN_WIDTH - m_ViewBox.w);
		//}
		//if (m_ViewBox.y > (2 * SCREEN_HEIGHT - m_ViewBox.h))//(2 * SCREEN_HEIGHT - m_ViewBox.h) tương tự với cách giải thích trên dùng để giới hạn chiều cao hoạt động của camera
		//{
		//	m_ViewBox.y = (2 * SCREEN_HEIGHT - m_ViewBox.h);
		//}

		m_Position = Vector2D(m_ViewBox.x, m_ViewBox.y);
		//khi lấy tọa độ hiện tại của nhân vật trừ cho m_ViewBox sau khi tính toán ta sẽ được tọa độ luôn ở giữa màn hình(trừ khi đến đã bị điểm giới hạn) vì vậy trình render sẽ luôn render nhân vật ở giữa màn hình
		//đối với map vì map không di chuyển như nhân vật nên khi trừ cho m_ViewBox map sẽ thoát khỏi không gian render của camera và không được render trong camera

	}
}