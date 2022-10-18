#include "stdafx.h"
#include "TileLayer.h"

TileLayer::TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesets)
	:mTilesize(tilesize), mTileMap(tilemap), mColCount(colcount), mRowCount(rowcount), mTilesets(tilesets)
{
	for (unsigned int i = 0; i < mTilesets.size(); i++)
	{
		TextureManager::getInstance()->Load(mTilesets[i].Name, "assets/Map/" + mTilesets[i].Source);
	}
}

void TileLayer::Render()
{
	//std::cout << mTilesets[1].Name;
	for (unsigned int i = 0; i < unsigned(mRowCount); i++)
	{
		for (unsigned int j = 0; j < unsigned(mColCount); j++)
		{

			int index = 0;
			int tileID = mTileMap[i][j];//mTileMap là các ID được truyền từ ParseTileMap 


			if (tileID == 0)//chỉ nhận các tileID khác 0, vì chúng ta sẽ không vẽ gì với giá trị 0 lên window
			{
				continue;
			}
			//bắt đầu lại vòng lặp để tăng hiệu suất, vì map sở hữu một lượng lớn lile,nếu kiểm tra hết sẽ giảm hiệu suất render
			else//chuyển id thành giá trị thực sự để sử dụng
			{

				if (mTilesets.size() > 1)//nếu có nhiều hơn 1 tileset(hình ảnh ta dùng để push vào map) thì ta không cần phải kiếm tra vì nó có nghĩa tileset nằm ở vị trí đầu tiên(thứ nhất)
				{
					for (unsigned int k = 1; k < mTilesets.size(); k++)
					{

						if (tileID >= mTilesets[k].FirstID && tileID <= mTilesets[k].LastID)
						{
							tileID = tileID + mTilesets[k].TileCount - mTilesets[k].LastID;//nếu ta có nhiều hơn 1 tileset thì id của các tileset thứ 2 trở đi sẽ có sự khác biệt, trong file xml nó sẽ được cộng dồn lên từ ID của các tiles trước, nhưng trong bản thân hình ảnh id của nó luôn được bắt đầu từ 0, vì vậy phép toán này giúp ta chuyển ID của XML về ID của hình ảnh thật sự.(còn ở tileset đầu tiên id sẽ chính xác như trên hình ảnh của nó vì vậy ta không cần phải tính toán do đó nếu chỉ có một tileset ta có thể bỏ qua phần này) ví dụ lấy ID trong file name = background firstgid = fisrt id = 26936 ,last id = 27188, tilecount = 252, => tile id = 5

							//std::cout<<" "<< tileID;
							index = k;//vị trí của tile set (ta sẽ có nhiều tile set vì vậy ta muốn biết chính xác ID này thuộc, đến từ tileset nào để push vào window)
							break;
						}
					}
				}
				Tileset ts = mTilesets[index];

				int	tileRow = tileID / ts.ColCount;// kiểm tra ô đó thuộc hàng nào của tilesets
				//std::cout << "Row" << tileRow << std::endl;

				int tileCol = tileID - tileRow * ts.ColCount - 1;//kiểm tra ô đó thuộc cột nào của tilesets

				//std::cout << "Col" << tileCol << std::endl;

				//if this tile is on the last column
				if (tileID % ts.ColCount == 0)
				{
					tileRow--;
					tileCol = ts.ColCount - 1;
				}
				TextureManager::getInstance()->DrawTile(ts.Name, ts.TileSize, j * ts.TileSize, i * ts.TileSize, tileRow, tileCol);//vị trí [i][j] chính là vị trí trong matrix của layer mà ta cần in
			}
		}
	}
}

void TileLayer::Update()
{
}

void TileLayer::RgidMap()
{

	for (unsigned int i = 0; i < unsigned(mRowCount); i++)
	{
		for (unsigned int j = 0; j < unsigned(mColCount); j++)
		{
			//mTileMap là các ID được truyền từ ParseTileMap
			if (mTileMap[i][j] > 0)
			{
				SDL_FRect Tile{ j * 16,i * 16, 16, 16 };
				mCollisionRect.emplace_back(Tile);
			}
		}
	}
}

TileMap TileLayer::getTileMap()
{
	 return mTileMap; 
}

int TileLayer::getTilesize()
{
	return mTilesize;
}

int TileLayer::getRowCount()
{
	return mRowCount;
}

int TileLayer::getColCount()
{
	return mColCount;
}

std::vector<SDL_FRect> TileLayer::getCollisionRect()
{
	return mCollisionRect;
}
