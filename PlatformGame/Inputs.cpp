#include "stdafx.h"
#include "Inputs.h"

Inputs* Inputs::sInstance = nullptr;

Inputs::Inputs()
{
	mKeyStates = SDL_GetKeyboardState(nullptr);//khởi tạo giá trị ban đầu cho m_KeyStates
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

bool Inputs::getKeyDown(SDL_Scancode key)
{
	if (mKeyStates[key] == 1)
	{
		return true;
	}
	return false;
}


void Inputs::KeyUp()
{
	mKeyStates = SDL_GetKeyboardState(nullptr);//kiểm tra có input từ bàn phím hay không, chưa cần truyền tham số.
}
int Inputs::getKeyUp(SDL_Event event)
{
	return 0;
}

void Inputs::KeyDown()
{
	mKeyStates = SDL_GetKeyboardState(nullptr);

}

int Inputs::getAxisKey(Axis axis)
{
	switch (axis)
	{
	case HORIZONTAl: //trucj docj
		if (getKeyDown(SDL_SCANCODE_D))
			return 1;
		if (getKeyDown(SDL_SCANCODE_A))
			return -1;
		break;

	case VERTICAL://truc ngang
		if (getKeyDown(SDL_SCANCODE_W))
			return 1;
		if (getKeyDown(SDL_SCANCODE_S))
			return -1;
		break;

	default:
		return 0;
	}

}