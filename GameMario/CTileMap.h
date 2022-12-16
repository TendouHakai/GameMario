#pragma once
#include <vector>
#include<D3DX10math.h>
#include <unordered_map>

#include "Sprite.h"
#include "Textures.h"
#include "debug.h"
#include "tinyxml.h"
#include "Utils.h"

using namespace std;

class CTileMap
{
private:
	vector<int> lpTile;

	unordered_map<int, LPSPRITE> lpMapSprites;

	int tileXSize;
	int tileYSize;
	int numXTiles, numYTiles;
	int startX, startY, endX, endY;
public:
	CTileMap(string filePath);
	~CTileMap();
	void LoadTile(string filePath);
	void SetTileRender(D3DXVECTOR2 start, D3DXVECTOR2 end);

	void Render();
};

