#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "TileLayer.h"

class GameMap//Map được xây trên các lớp (layer)
{
public:
	void Render()
	{
		for (const auto& layer : m_MapLayers)
		{
			layer->Render();
		}
	}
	void Update()//update các layer nếu bị chỉnh sửa
	{
		for (const auto& layer : m_MapLayers)
		{
			layer->Update();
		}
	}
	void Clean()
	{
		for (const auto& layer : m_MapLayers)
		{
			delete layer;
		}
		m_MapLayers.clear();
	}
	std::vector<TileLayer*> GetMapLayers() { return m_MapLayers; }// vì map sẽ tương tác với một số object nên ta cần hàm này 
private:
	friend class MapParser;//cho phép class MapParser truy cập vào biến private của class này
	std::vector<TileLayer*> m_MapLayers;

};

#endif
