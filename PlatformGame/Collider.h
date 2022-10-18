#ifndef COLLIDER_H
#define COLLIDER_H


class Collider
{
public:
	SDL_Rect GetBox() { return m_Box; }
	void SetBuffer(int x, int y, int w, int h) { m_Buffer = { x,y,w,h }; }
	SDL_Rect GetBuffer() { return m_Buffer; }
	void Set(int x, int y, int w, int h)//thường box của nhân vật sẽ có các khoảng trống thừa ta dùng phương thức này này để xóa đi những chỗ trống đó
	{
		m_Box =
		{
			x - m_Buffer.x,
			y - m_Buffer.y,
			w - m_Buffer.w,
			h - m_Buffer.h
		};
	}
	void SetTileSetBox1(int x, int y, int w, int h)
	{
		m_TileSetBox1 = { x,y,w,h };
	}
	void SetTileSetBox2(int x, int y, int w, int h)
	{
		m_TileSetBox2 = { x,y,w,h };
	}
	void SetSkillHitBox(SDL_Rect skillhitbox)
	{
		m_SkillHitBox = skillhitbox;
	}

	SDL_Rect GetSkillHitBox() { return m_SkillHitBox; }
	SDL_Rect GetTileSetBox1() { return m_TileSetBox1; }
	SDL_Rect GetTileSetBox2() { return m_TileSetBox2; }

	size_t operator	()(const SDL_Rect& obj) const
	{
		return (uint64_t(obj.y) << 32 | uint64_t(obj.x));
	}
private:

	SDL_Rect m_rect;
	SDL_Rect m_TileSetBox1;
	SDL_Rect m_TileSetBox2;
	SDL_Rect m_SkillHitBox;
	SDL_Rect m_Box;
	SDL_Rect m_Buffer;
};

#endif 