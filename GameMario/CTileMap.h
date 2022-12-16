#pragma once
#include <vector>
#include <unordered_map>
#include <D3DX10math.h>

#include "Sprite.h"
#include "Textures.h"
#include "debug.h"
#include "tinyxml.h"
#include "Utils.h"

using namespace std;

class CTileMap
{
private:
	vector<int> Gids;
	unordered_map<int, LPSPRITE> tileMapSprites;
	int tileWidth, tileHeight;
	int xTiles, yTiles;
	int xStart, yStart, xEnd, yEnd;
public:
	CTileMap(string filePath) {
		LoadTileMap(filePath);
	}
	~CTileMap() {
		for (auto x : tileMapSprites)
		{
			LPSPRITE s = x.second;
			delete s;
		}

		tileMapSprites.clear();
	}
	void LoadTileMap(string filePath);
	void SetTileRender(float xstart, float ystart, float xend, float yend);

	void Render();
};

