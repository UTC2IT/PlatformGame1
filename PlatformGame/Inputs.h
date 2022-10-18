﻿#ifndef INPUT_H
#define INPUT_H

#include "Game.h"

enum Axis { HORIZONTAl, VERTICAL };//HORIZONTAL là theo chiều ngang, VERTICAL là theo chiều dọc

class Inputs
{
public:
	static Inputs* GetInstance()//ta chỉ cần 1 Instance của class này cho toàn bộ chương trình để tránh xung đột(ví dụ như có 2 event được truyền vào cùng lúc máy tính sẽ không biết input event nào trước.
	{
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new Inputs();
	}

	void Listen();
	bool GetKeyDown(SDL_Scancode key); //https://wiki.libsdl.org/SDL_Scancode
	int GetKeyUp(SDL_Event event);
	int GetAxisKey(Axis axis);
private:
	Inputs();

	void KeyUp();
	void KeyDown();
	const Uint8* m_KeyStates;//(Unit8* có cùng kích thước bit nhưng không thể lưu trữ giá trị âm, lưu trữ giá trị được nhập từ bàn phím(event) , nếu trả về 1: input thành công, trả về 0: không có gì xảy ra.

	static Inputs* s_Instance;
};

#endif

