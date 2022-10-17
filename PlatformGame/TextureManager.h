#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "Game.h"

class TextureManager
{
private:
	std::map < std::string, SDL_Texture*> mTextureMap; //Tìm hiểu thêm thông qua: https://www.youtube.com/watch?v=5j1FTGu6HlE
	static TextureManager* sInstance;
public:
	static TextureManager* getInstance() //ta chỉ cần 1 Instance của class này cho toàn bộ chương trình để tránh xung đột
	{
		return sInstance = (sInstance != nullptr) ? sInstance : new TextureManager();
	}

	bool Load(std::string id, std::string filename); // load cấu trúc hình ảnh từ file
	bool ParseTextures(std::string source);
	void Drop(std::string id); //Loại bỏ cấu trúc hình ảnh
	void Clean(); //xóa tất cả cấu trúc khỏi bộ nhớ

	void DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void Draw(std::string id, int x, int y, int width, int height, float scaleX, float scaleY, float scrollRatio, SDL_RendererFlip flip = SDL_FLIP_NONE); //vẽ đối tượng tĩnh(texture)
	void DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE); // row là hành hình ảnh được Render ra với mỗi thao tác ta sẽ có một animation khác nhau vì vậy ta sẽ có nhiều raw chứa nhiều hoạt ảnh khác nhau(row bắt đầu từ 0)
	void DrawFrameCol(std::string id, int x, int y, int width, int height, int col, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
};
#endif // !TEXTUREMANAGER
