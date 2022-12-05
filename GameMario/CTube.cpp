#include "CTube.h"

void CTube::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - cell_width/2;
	top = y - cell_height/2;
	right = left + cell_width*2;
	bottom = top + cell_height*height;
}

void CTube::Render()
{
	if (this->height <= 0) return;

	float yy = y;
	CSprites* s = CSprites::GetInstance();
	s->Get(this->idSpriteTL)->Draw(x, yy);
	s->Get(this->idSpriteTR)->Draw(x+cell_width, yy);
	yy += cell_height;
	// render giua
	for (int i = 1; i < height; i++) {
		s->Get(this->idSpriteML)->Draw(x, yy);
		s->Get(this->idSpriteMR)->Draw(x+cell_width, yy);
		yy += cell_height;
	}
	if (height > 1)
	{
		s->Get(this->idSpriteBL)->Draw(x, yy);
		s->Get(this->idSpriteBR)->Draw(x + cell_width, yy);
	}
	//RenderBoundingBox();
}
