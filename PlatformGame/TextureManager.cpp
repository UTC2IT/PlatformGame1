#include "stdafx.h"
#include "TextureManager.h"


TextureManager* TextureManager::sInstance = nullptr;

TextureManager* TextureManager::getInstance()
{
	return sInstance = (sInstance != nullptr) ? sInstance : new TextureManager();
}

bool TextureManager::Load(std::string id, std::string filename)
{
	SDL_Surface* surface = IMG_Load(filename.c_str());//chuyển hình ảnh thành texture(pixel) bề mặt (convert string to char)
	if (surface == nullptr)
	{
		SDL_Log("Falled to load texture: %s, %s", filename.c_str(), SDL_GetError());
		return false;
	}
	//nếu mọi thứ đều đúng -> tạo texture
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::getInstance()->getRenderer(), surface);//tham số đầu tiên là trình Render, tham số thứ 2 là cấu trúc SDL_Surface chứa dữ liệu pixel được sử dụng để lấp đầy texture
	if (texture == nullptr)
	{
		SDL_Log("Falled to load texture from surface: %s", SDL_GetError());
		return false;
	}
	//nếu mọi thứ đều đúng -> thêm texture vào và return true
	mTextureMap[id] = texture;
	return true;
}

bool TextureManager::ParseTextures(std::string source)
{
	TiXmlDocument xml;

	xml.LoadFile(source);
	if (xml.Error())
	{
		std::cout << "Failed to load " << source << std::endl;
		return false;
	}

	TiXmlElement* root = xml.RootElement();// root đầu tiên của file
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("texture"))//kiểm tra nếu element là texture thì vào bên trong lớp texture để kiểm tra id, source 
		{
			//lấy id và source 
			std::string	id = e->Attribute("id");
			std::string src = e->Attribute("source");
			Load(id, src);
		}
	}
	return true;
}

void TextureManager::DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip)
{

	SDL_FRect srcRect = { tileSize * frame, tileSize * row, tileSize , tileSize };//soure điểm đầu của ảnh
	Vector2D cam = Camera::getInstance()->getPosition();

	SDL_FRect dstRect = { x - cam.getX(), y - cam.getY(), tileSize,tileSize };//destination đích đến của ảnh

	SDL_RenderCopyEx(Game::getInstance()->getRenderer(), mTextureMap[tilesetID], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, float scaleX = 1, float scaleY = 1, float scrollRatio = 1, SDL_RendererFlip flip)
{
	SDL_FRect srcRect = { 0, 0, width, height };//điểm đầu của source ảnh muốn vẽ vào
	Vector2D cam = Camera::getInstance()->getPosition() * scrollRatio;
	SDL_FRect dstRect = { x - cam.getX(), y - cam.getY(), width * scaleX, height * scaleY };//điểm in của ảnh trong window


	SDL_RenderCopyEx(Game::getInstance()->getRenderer(), mTextureMap[id], &srcRect, &dstRect, 0, nullptr, flip); //xoay đối tượng, tham số thứ nhất là trình render, tham số thứ 2 là texture đưa vào cửa sổ, tham số thứ 3 là địa chỉ sourceRect, tham số thứ 4 là địa chỉ destinationRect, tham số thứ 5 là góc bạn muốn quay, tham số thứ 6 điểm căn giữa, tham số cuối cách đối tượng định hướng(lật theo chiều ngang hoặc dọc)

}
void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip)
{
	SDL_FRect srcRect = { (width * frame),(height * row), width, height };

	Vector2D cam = Camera::getInstance()->getPosition();

	SDL_FRect dstRect = { x - cam.getX() ,y - cam.getY(), width, height };

	SDL_RenderCopyEx(Game::getInstance()->getRenderer(), mTextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawFrameCol(std::string id, int x, int y, int width, int height, int col, int frame, SDL_RendererFlip flip)
{
	SDL_FRect srcRect = { (width * col),(height * frame), width, height };

	Vector2D cam = Camera::getInstance()->getPosition();

	SDL_FRect dstRect = { x - cam.getX() ,y - cam.getY(), width, height };

	SDL_RenderCopyEx(Game::getInstance()->getRenderer(), mTextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}


void TextureManager::Drop(std::string id)
{
	SDL_DestroyTexture(mTextureMap[id]);//chỉ phá hủy texture element nhưng không xóa khỏi map, lúc này nó là một con trỏ null
	mTextureMap.erase(id);//xóa khỏi bán đồ
}

void TextureManager::Clean()//dọn dẹp tất cả texture khi đóng ứng dụng
{
	std::map<std::string, SDL_Texture*> it;
	for (auto& x : it)
	{
		SDL_DestroyTexture(x.second);
	}
	mTextureMap.clear();
	SDL_Log("texture map cleaned!!! ");
}

