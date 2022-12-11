#include "GameObject.h"

class CBLockEnemies : public CGameObject
{
protected:
	float height;
	float width;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {
		left = x - width / 2;
		top = y - height / 2;
		right = left + width;
		bottom = top + height;
	}
	virtual void Render() { 
		//RenderBoundingBox(); 
	}
public:
	CBLockEnemies(float x, float y, float width, float height) :CGameObject(x, y) { this->height = height; this->width = width; }
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
};