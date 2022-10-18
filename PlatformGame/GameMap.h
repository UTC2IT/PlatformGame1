#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "TileLayer.h"

class GameMap//Map được xây trên các lớp (layer)
{
private:
	friend class MapParser;//cho phép class MapParser truy cập vào biến private của class này
	std::vector<TileLayer*> mMapLayers;
public:
	void Render();
	void Update();//update các layer nếu bị chỉnh sửa
	void Clean();
	std::vector<TileLayer*> getMapLayers();// vì map sẽ tương tác với một số object nên ta cần hàm này 
};

#endif
