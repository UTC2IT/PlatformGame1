#ifndef MAPPARSE_H
#define MAPPARSE_H

#include "GameMap.h"

class MapParser//"phân tích cú pháp" phân tích file XML
{
public:

	GameMap* GetMaps(std::string id) { return m_MapsDict[id]; }

	void Clean();
	GameMap* Parse(std::string id, std::string source);
	static MapParser* GetInstance()//ta chỉ cần 1 Instance của class này cho toàn bộ chương trình để tránh xung đột
	{
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new MapParser();
	}
private:

	Tileset ParseTileset(TiXmlElement* xmlTileset);
	TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount);
private:
	MapParser() {}
	static MapParser* s_Instance;
	std::map<std::string, GameMap*> m_MapsDict;
};

#endif
