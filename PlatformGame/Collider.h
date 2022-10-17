#ifndef COLLIDER_H
#define COLLIDER_H
class Collider
{
private:
	SDL_FRect mrect;
	SDL_FRect mTileSetBox1;
	SDL_FRect mTileSetBox2;
	SDL_FRect mSkillHitBox;
	SDL_FRect mBox;
	SDL_FRect mBuffer;
public:
	SDL_FRect getBox();
	void setBuffer(float x,float y,float w,float h);
	SDL_FRect getBuffer();
	void setBox(float x, float y, float w, float h);//Thường box của nhân vật sẽ có các khoảng cách
	//trống ,ta thường dùng phương thức này để xóa đi những chỗ trống đó
	void setTileSetBox1(float x, float y, float w, float h);
	void setTileSetBox2(float x, float y, float w, float h);
	void setSkillHitBox(SDL_FRect skillhitbox);
	SDL_FRect getSkillHitBox();
	SDL_FRect getTileHitBox1();
	SDL_FRect getTileHitBox2();
};

#endif
