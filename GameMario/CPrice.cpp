#include "CPrice.h"

void CPrice::Render() {
	CAnimations::GetInstance()->Get(ID_ANI_PRICE_100)->Render(x, y);
}