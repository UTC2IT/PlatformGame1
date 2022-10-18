#include "stdafx.h"
#include "Inputs.h"

Inputs* Inputs::sInstance = nullptr;

Inputs::Inputs()
{
	m_KeyStates = SDL_GetKeyboardState(nullptr);//khởi tạo giá trị ban đầu cho m_KeyStates
}
void Inputs::Listen()
{
	SDL_Event event;//https://wiki.libsdl.org/SDL_Event

	while (SDL_PollEvent(&event))//Trả về 1 nếu có sự kiện đang chờ xử lý hoặc 0 nếu không có sự kiện nào khả dụng. https://wiki.libsdl.org/SDL_PollEvent
	{
		switch (event.type)
		{
		case SDL_QUIT:
			Game::getInstance()->Quit();
			break;
		case SDL_KEYDOWN://Sự kiện SDL_KEYDOWN hoặc SDL_KEYUP xảy ra bất cứ khi nào người dùng nhấn hoặc thả một nút trên bàn phím. Thông tin về phím nào đã được nhấn hoặc nhả ra nằm trong thành viên của bộ phím .
			KeyDown();
			break;
		case SDL_KEYUP:
			KeyUp();
			break;
		}
	}
}

bool Inputs::GetKeyDown(SDL_Scancode key)
{
	if (m_KeyStates[key] == 1)
	{
		return true;
	}
	return false;
}


void Inputs::KeyUp()
{
	m_KeyStates = SDL_GetKeyboardState(nullptr);//kiểm tra có input từ bàn phím hay không, chưa cần truyền tham số.
}
int Inputs::GetKeyUp(SDL_Event event)
{
	return 0;
}

void Inputs::KeyDown()
{
	m_KeyStates = SDL_GetKeyboardState(nullptr);

}

int Inputs::GetAxisKey(Axis axis)
{
	switch (axis)
	{
	case HORIZONTAl:
		if (GetKeyDown(SDL_SCANCODE_D))
			return 1;
		if (GetKeyDown(SDL_SCANCODE_A))
			return -1;
		break;

	case VERTICAL:
		if (GetKeyDown(SDL_SCANCODE_W))
			return 1;
		if (GetKeyDown(SDL_SCANCODE_S))
			return -1;
		break;

	default:
		return 0;
	}

}