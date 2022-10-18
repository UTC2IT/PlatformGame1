#ifndef TILELAYER_H
#define TILELAYER_H

#include "Layer.h"

struct Tileset //set Các thông số như ID, hàng, cột, số lượng ô,tên ô,nguồn của assets(tileset là các hình ảnh dùng để put vào)
{
	int FirstID, LastID;
	int RowCount, ColCount/*số cột của tileset(của file assets put vào map, không phải cột của map)*/;//hàng cột của tileset
	int TileCount /*số lượng ô của tileset*/, TileSize /*kích thước của tile (16*16,32*32,...)*/;
	std::string Name /*ví dụ: Tileset tên assets,Backgournd,Dark-Tre,... sẽ được TextureManager dùng để load và put vào window*/, Source /*đường dẫn của file*/;
};

using	TilesetList = std::vector<Tileset>;//mảng 1 chiều các tileset///*ví dụ: Tileset tên assets,Backgournd,Dark-Tre,... sẽ được TextureManager dùng để load và put vào window*/using dùng để tạo một định nghĩa mới, thay vì dùng vector khi ta khai báo TilesetList nó sẽ tự động hiểu là mảng 1 chiều các Tileset, TileMap cũng tương tự như vậy
using	TileMap = std::vector<std::vector<int> >;// mảng 2 chiều các tile 
class TileLayer : public Layer//chứa các tile được vẽ lên Layer, mỗi layer sẽ có các tile khác nhau
{
public:
	TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesets);
	virtual void Render();
	virtual void Update();
	void RgidMap();
	TileMap GetTileMap() { return m_TileMap; }//để dùng Biến m_TileMap ở các class khác(ví dụ như xử lý va chạm)
	int GetTilesize() { return m_Tilesize; }
	int GetRowCount() { return m_RowCount; }
	int GetColCount() { return m_ColCount; }
	std::vector<SDL_Rect> GetCollisionRect() { return m_CollisionRect; }
private:

	int m_Tilesize;
	int m_RowCount, m_ColCount;
	std::vector<SDL_Rect> m_CollisionRect;
	//Collider* m_Collider;
	TileMap m_TileMap;//mảng 2 chiều các ID tile
	TilesetList m_Tilesets;//mảng 1 chiều các tileset

};


#endif
