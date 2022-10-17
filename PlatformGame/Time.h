#ifndef TIME_H
#define	TIME_H

class Time
{
private:
	static Time* sTime;
	float mCurrenttime;
	float mLasttime;
	float mDeltatime;
public:
	Time();
	~Time();
	void Update();
	float getTick();
	float getCurrTick();
};

#endif