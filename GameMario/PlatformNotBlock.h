#pragma once
#include "Platform.h"
class CPlatformNotBlock : public CPlatform
{
public:
	CPlatformNotBlock(float x, float y,
		float cell_width, float cell_height, int length) : CPlatform(x, y, cell_width, cell_height, length){ }
	int IsBlocking() { return 1; }
	int IsCollidable() { return 0; }
};

