#include "CPrice.h"

void CPrice::Render() {
	switch (number)
	{
	case 1000: {
		CAnimations::GetInstance()->Get(ID_ANI_PRICE_1000)->Render(x, y);
		break;
	}
	case 200: {
		CAnimations::GetInstance()->Get(ID_ANI_PRICE_200)->Render(x, y);
		break;
	}
	case 1: {
		CAnimations::GetInstance()->Get(ID_ANI_PRICE_1M)->Render(x, y);
		break;
	}
	default:
		CAnimations::GetInstance()->Get(ID_ANI_PRICE_100)->Render(x, y);
		break;
	}
}