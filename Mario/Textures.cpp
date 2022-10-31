#include <Windows.h>

#include "debug.h"
#include "Game.h"
#include "textures.h"

CTextures* CTextures::__instance = NULL;

CTextures::CTextures()
{

}

CTextures* CTextures::GetInstance()
{
	if (__instance == NULL) __instance = new CTextures();
	return __instance;
}

void CTextures::Add(string id, LPCWSTR filePath)
{
	textures[id] = CGame::GetInstance()->LoadTexture(filePath);
}

LPTEXTURE CTextures::Get(string i)
{
	return textures[i];
}



