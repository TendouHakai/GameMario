#include "ChangeCam.h"

void ChangeCam::Render()
{
	RenderBoundingBox();
}

void ChangeCam::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - this->w / 2;
	t = y - this->h / 2;
	r = l + this->w;
	b = t + this->h;
}
