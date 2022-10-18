#ifndef MAPPARSE_H
#define MAPPARSE_H

#include "GameMap.h"

class MapParser//"phân tích cú pháp" phân tích file XML
{
public:

	GameMap* getMaps(std::string id);

	void Clean();
	GameMap* Parse(std::string id, std::string source);
	static MapParser* getInstance();//ta chỉ cần 1 Instance của class này cho toàn bộ chương trình để tránh xung đột
private:

	Tileset ParseTileset(TiXmlElement* xmlTileset);
	TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount);
private:
	MapParser() {}
	static MapParser* sInstance;
	std::map<std::string, GameMap*> mMapsDict;
};

#endif
