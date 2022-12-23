#include "CTileMap.h"

void CTileMap::LoadTileMap(string filePath)
{
	DebugOut(L"[INFO] Start loading tiles maps from : %s\n", ToLPCWSTR(filePath));
	TiXmlDocument doc(filePath.c_str());
	if (doc.LoadFile()) {
		TiXmlElement* Root = doc.RootElement();

		tileWidth = atoi(Root->Attribute("tilewidth"));
		tileHeight = atoi(Root->Attribute("tileheight"));
		xTiles = atoi(Root->Attribute("width"));
		yTiles = atoi(Root->Attribute("height"));

		Gids.resize(xTiles * yTiles);

		for (TiXmlElement* tileset = Root->FirstChildElement("tileset"); tileset != nullptr; tileset = tileset->NextSiblingElement()) {
			int firstgid;
			tileset->QueryIntAttribute("firstgid", &firstgid);
			// load texture của từng tileset
			for (TiXmlElement* image = tileset->FirstChildElement("image"); image != nullptr; image = image->NextSiblingElement()) {
				int texID = atoi(image->Attribute("texID"));
				CTextures* textures = CTextures::GetInstance();
				textures->Add(texID, ToLPCWSTR(image->Attribute("source")));
				LPTEXTURE texture = textures->Get(texID);

				// load sprite trong từng tileset
				int width, height;
				image->QueryIntAttribute("width", &width);
				image->QueryIntAttribute("height", &height);
				

				int XSprites = width / tileWidth;
				int YSprites = height / tileHeight;

				for (int i = 0; i < XSprites; i++)
					for (int j = 0; j < YSprites; j++)
					{
						LPSPRITE s = new CSprite(i + 1 + XSprites * j, (i * tileWidth), (j * tileHeight), (i * tileWidth) + tileWidth - 1, (j * tileHeight) + tileHeight - 1, texture);
						tileMapSprites[i + firstgid + XSprites * j] = s;
					}
			}
		}
		// load ma trận gid
		int numgid = 0;
		for (TiXmlElement* layer = Root->FirstChildElement("layer"); layer != nullptr; layer = layer->NextSiblingElement()) {
			for (TiXmlElement* data = layer->FirstChildElement("data"); data != nullptr; data = data->NextSiblingElement()) {
				for (TiXmlElement* gid = data->FirstChildElement("tile"); gid != nullptr; gid = gid->NextSiblingElement()) {
					gid->QueryIntAttribute("gid", &Gids[numgid]);
					numgid++;
				}
			}
		}
	}
	else {
		DebugOut(L"[ERROR] Failed to load tilemap from: %s\n", ToLPCWSTR(filePath));
		return;
	}
	DebugOut(L"[INFO] Done loading tilemap from: %s\n", ToLPCWSTR(filePath));
}

void CTileMap::SetTileRender(float leftCam, float topCam, float rightCam, float bottomCam)
{
	this->xStart = (int)((leftCam)/tileWidth);
	this->yStart = (int)((topCam)/tileHeight);
	this->xEnd = ceil((rightCam) / tileWidth);
	this->yEnd = ceil((bottomCam) / tileHeight);

	if (xStart < 0)
		xStart = 0;
	else if(xStart>xTiles)
		xStart = xTiles-1;

	if (yStart < 0)
		yStart = 0;
	else if (yStart > yTiles)
		yStart = yTiles - 1;

	if (xEnd < 0)
		xEnd = 0;
	else if (xEnd > xTiles)
		xEnd = xTiles - 1;

	if (yEnd < 0)
		yEnd = 0;
	else if (yEnd > yTiles)
		yEnd = yTiles - 1;
}

void CTileMap::Render()
{
	for (int i = xStart; i < xEnd; i++) {
		for (int j = yStart; j < yEnd; j++)
		{
			int pid = Gids[i + j * xTiles];
			
			if (pid != 1)
				tileMapSprites[pid]->Draw(i * tileWidth + 8, j * tileHeight + 8);
		}
	}
}


