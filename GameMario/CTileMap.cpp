#include "CTileMap.h"

CTileMap::CTileMap(string filePath)
{
    LoadTile(filePath);
}

CTileMap::~CTileMap()
{
    for (auto x : lpMapSprites)
    {
        LPSPRITE s = x.second;
        delete s;
    }

    lpMapSprites.clear();

}

void CTileMap::LoadTile(string filePath)
{
    DebugOut(L"[INFO] Start loading tiles assets from : \"%s\"\n", filePath);
    TiXmlDocument doc(filePath.c_str());
    if (doc.LoadFile())
    {
        TiXmlElement* Root = doc.RootElement();
        if (Root)
        {
            lpTile.clear();
            Root->QueryIntAttribute("tilewidth", &tileXSize);
            Root->QueryIntAttribute("tileheight", &tileYSize);
            Root->QueryIntAttribute("width", &numXTiles);
            Root->QueryIntAttribute("height", &numYTiles);


            /*int r = 0, g = 0, b = 0, a = 0;
            Root->QueryIntAttribute("r", &r);
            Root->QueryIntAttribute("g", &g);
            Root->QueryIntAttribute("b", &b);
            Root->QueryIntAttribute("b", &a);*/

            //D3DXCOLOR backGroundColor = D3DXCOLOR((float)r / 255, (float)g / 255, (float)b / 255, (float)a / 255);
            lpTile.resize(numXTiles * numYTiles);

            for (TiXmlElement* tileset = Root->FirstChildElement(); tileset != nullptr; tileset = tileset->NextSiblingElement())
            {
                int texID = atoi(tileset->Attribute("texID"));
                CTextures* textures = CTextures::GetInstance();
                textures->Add(texID, ToLPCWSTR(tileset->Attribute("texturePath")));
                LPTEXTURE texture = textures->Get(texID);

                int width, height;
                tileset->QueryIntAttribute("width", &width);
                tileset->QueryIntAttribute("height", &height);

                int numXSprite = width / tileXSize;
                int numYSprite = height / tileYSize;

                for (int i = 0; i < numXSprite; i++)
                    for (int j = 0; j < numYSprite; j++)
                    {
                        LPSPRITE s = new CSprite(i + 1 + numXSprite * j,(i * tileXSize), (j * tileYSize), (i * tileXSize)+tileXSize-1, (j * tileYSize)+ tileYSize-1, texture);
                        lpMapSprites[i + 1 + numXSprite * j] = s;
                    }
                int num = 0;
                for (TiXmlElement* tileNode = tileset->FirstChildElement(); tileNode != nullptr; tileNode = tileNode->NextSiblingElement())
                {
                    tileNode->QueryIntAttribute("gid", &lpTile[num]);
                    num++;
                }
            }
        }
    }
    else
    {
        DebugOut(L"[ERROR] Failed to load tilemap file: %s\n", ToLPCWSTR(filePath));
        return;
    }
    DebugOut(L"[INFO] Done loading tilemap from: %s\n", ToLPCWSTR(filePath));
}


void CTileMap::SetTileRender(D3DXVECTOR2 start, D3DXVECTOR2 end)
{
    startX = (int)(start.x / tileXSize);
    startY = (int)(start.y / tileYSize);

    if (startX < 0) startX = 0;
        else if (startX >= numXTiles) startX = numXTiles - 1;

    if (startY < 0) startY = 0;
        else if (startY >= numYTiles) startY = numYTiles - 1;
    //convert to upper
    endX = ceil(end.x / tileXSize);
    endY = ceil(end.y / tileYSize);
    if (endX < 0) endX = 0;
    else if (endX >= numXTiles) endX = numXTiles - 1;
    if (endY < 0) endY = 0;
    else if (endY >= numYTiles) endY = numYTiles - 1;

}

void CTileMap::Render()
{
    for (int i = startX; i <= endX; i++)
        for (int j = startY; j <= endY; j++)
        {
            int pid = lpTile[i + j * numXTiles];
            if (pid != 1)
                lpMapSprites[pid]->Draw(i * tileXSize + 8, j * tileYSize + 8);
        }
}