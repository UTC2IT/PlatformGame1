#include "stdafx.h"
#include "MapParse.h"


MapParser* MapParser::sInstance = nullptr;


GameMap* MapParser::getMaps(std::string id)
{
	return mMapsDict[id];
}

void MapParser::Clean()
{
	std::map<std::string, GameMap*>::iterator it;
	for (it = mMapsDict.begin(); it != mMapsDict.end(); it++)
	{
		it->second = nullptr;
	}
	mMapsDict.clear();
}

GameMap* MapParser::Parse(std::string id, std::string source)//Parse : phân tích
{
	TiXmlDocument xml;

	xml.LoadFile(source);

	if (xml.Error())//kiểm tra file XML có được mở đúng và chính xác không, dễ dàng trong việc check lỗi
	{
		std::cerr << "Failed to load: " << source << std::endl;
		//return false;
	}
	TiXmlElement* root = xml.RootElement();//phần tử đầu tiên của tệp XML (cụ thể là map trong tệp XML đang xét)

	int rowcount, colcount, tilesize = 0;

	root->Attribute("width", &colcount);//lấy chiều rộng của map(root element là map)
	root->Attribute("height", &rowcount);//lấy chiều cao của map
	root->Attribute("tilewidth", &tilesize);//lấy về số bit, 16, 32, 64bit từ XML//pixel đa số đều là hình vuông nên không cần phải tìm giá trị height

	//Parse Tile sets
	TilesetList	tilesets;
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())//Giả sử có rất nhiều tileset(mở file tmx trong notepad để rõ hơn), thì giải pháp tốt nhất là sẽ sử dụng vòng lặp để duyệt qua tất cả các element và check xem đâu là element chứa các giá trị của tilesets
	{
		if (e->Value() == std::string("tileset"))
		{
			tilesets.push_back(ParseTileset(e));//sau khi lấy các giá trị của biến thuộc struct tileset thông qua hàm ParseTileset - tiếp tục đến các element (tilesets) khác phân tích để push vào chuỗi tilesets
		}
	}

	//Parse Layer
	GameMap* gamemap = new GameMap();
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())//duyệt từ element đầu đến cuối để tìm element layer
	{

		if (e->Value() == std::string("layer"))
		{
			TileLayer* tilelayer = ParseTileLayer(e, tilesets, tilesize, rowcount, colcount);//truyền các tham số vào hàm ParseTileLayer(hàm return) để xử lý dữ liệu
			gamemap->mMapLayers.emplace_back(tilelayer);//sau khi xử lý xong push tilelayer vào mảng m_MapLayer(mảng các tilelayer)
		}
	}
	mMapsDict[id] = gamemap;//lưu value gamemap vào key id
	return mMapsDict[id];
}

MapParser* MapParser::getInstance()
{
	return sInstance = (sInstance != nullptr) ? sInstance : new MapParser();
}

Tileset MapParser::ParseTileset(TiXmlElement* xmlTileset)// phân tích tileset, trả về các thông số của tileset(dữ liệu của một ô) trong tệp xml,<tileset firstgid="1226" name="Background" tilewidth="16" tileheight="16" tilecount="384" columns="24">, các phần tử firstgid, name... là các child , phần thử đầu tiên được gọi là FisrtChildElement và phần tử kế tiếp là NextSiblingElement
{
	Tileset tileset;
	tileset.Name = xmlTileset->Attribute("name");
	xmlTileset->Attribute("firstgid", &tileset.FirstID);//gán firstgid cho FirstID

	xmlTileset->Attribute("tilecount", &tileset.TileCount);
	tileset.LastID = (tileset.FirstID + tileset.TileCount) - 1;// -1 vì ID đầu tiên là 1

	xmlTileset->Attribute("columns", &tileset.ColCount);
	tileset.RowCount = tileset.TileCount / tileset.ColCount;
	xmlTileset->Attribute("tilewidth", &tileset.TileSize);//chỉ cần biết số pixel(16px,32px,64px) của width hoặc height vì đây là pixel

	TiXmlElement* image = xmlTileset->FirstChildElement();//image là một first child, tile set, data cx là một FirstChildElement
	tileset.Source = image->Attribute("source");
	//std::cout << tileset.Source;

	return tileset;

}

TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount)// phân tích layer, trả về thống số cho các biến trong Tilelayer
{
	TiXmlElement* data = xmlLayer->FirstChildElement();//khởi tạo data như một nullptr, có thể gán trực tiếp data = nullptr

	for (TiXmlElement* e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())//FirstChild: data con đầu tiên,NextSibling: data "anh chị" kế tiếp, một id được đại diện cho 1 child
	{
		if (e->Value() == std::string("data"))
		{
			data = e;// chỉ chứa 1 data trong bản đồ, vì vậy khi tìm thấy data -> break
			break;
		}
	}

	std::string matrix(data->GetText());//truyền ma trận của layer đang xét vào matrix
	// std::string matrix(data->getText());//truy cập vào văn bản bên trong một phần tử(truy cập vào các nút con)
	// std::cout << matrix;
	std::stringstream iss(matrix);//lưu matrix vào iss và lưu vào buffer
	std::string id;

	TileMap tilemap(rowcount, std::vector<int>(colcount, 0));//tạo một mảng hai chiều kích thước [rowcount][colcount] với các phần tử = 0
	for (int row = 0; row < rowcount; row++)
	{
		for (int col = 0; col < colcount; col++)
		{
			getline(iss, id, ',');//khi tìm thấy dấu phẩy thì đặt giá trị của từ buffer của iss vào id, vì ma trận trong data các phần tử được ngăn cách bới dấu phẩy
			//std::cout << id;
			std::stringstream convertor(id);//chuyển id(string) sang convertor(int) và lưu vào buffer
			convertor >> tilemap[row][col];//truyền từ convertor vào tilemap
			if (!iss.good())//kiểm tra xem luồng này có phát sinh lỗi nào hay không,Phương thức này trả về true nếu luồng tốt, ngược lại là false.
				break;
		}
	}
	return (new TileLayer(tilesize, rowcount, colcount, tilemap, tilesets));
}