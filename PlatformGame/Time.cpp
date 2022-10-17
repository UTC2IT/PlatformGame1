#include "Time.h"
#include "stdafx.h"

Time::Time()
{
 
}

Time::~Time()
{
}

void Time::Update()
{
	this->mDeltatime = (float)(SDL_GetTicks64() - this->mLasttime) * (10000.0f/ (float)SDL_GetPerformanceFrequency());//chia (1000 miligiay = 1s)

	if (this->mDeltatime > 1.5)// đặt giới hạn cho deltatime nếu vượt quá giá trị cho phép(1.5 milisecond) mọi thứ có thể nhảy ra khỏi ví trí của nó, tệ nhất là không nhìn thấy gì, việc này giúp hoạt ảnh hoạt động nhất quán không nhanh hoặc chậm hơn tại mọi thời gian
		this->mDeltatime = 1.5;

	this->mLasttime = (float)SDL_GetTicks64();
}

float Time::getTick()
{
    return this->mDeltatime;
}

float Time::getCurrTick()
{
	return this->mLasttime;
}
