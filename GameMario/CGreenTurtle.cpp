#include "CGreenTurtle.h"

void CGreenTurtle::Render()
{
	int aniID;

	switch (state)
	{
	case TURTLE_STATE_WALK: {
		if (vx > 0) {
			aniID = ID_ANI_GREENTURTLE_WALK_RIGHT;
		}
		else aniID = ID_ANI_GREENTURTLE_WALK_LEFT;
		break;
	}
	case TURTLE_STATE_DEAD: {
		aniID = ID_ANI_GREENTURTLE_DEAD;
		break;
	}
	case TURTLE_STATE_REVIVAL: {
		aniID = ID_ANI_GREENTURTLE_REVIVAL;
		break;
	}
	case TURTLE_STATE_DEAD_TAILTURNING: {
		aniID = ID_ANI_GREENTURTLE_DEAD_TAILTURNING;
		break;
	}
	case TURTLE_STATE_KICKED_RIGHT: {
		aniID = ID_ANI_GREENTURTLE_KICK;
		break;
	}
	case TURTLE_STATE_KICKED_LEFT: {
		aniID = ID_ANI_GREENTURTLE_KICK;
		break;
	}
	case GREENTURTLE_STATE_COLLECTION_RIGHT: {
		aniID = ID_ANI_GREENTURTLE_DEAD_TAILTURNING;
		break;
	}
	case GREENTURTLE_STATE_COLLECTION_LEFT: {
		aniID = ID_ANI_GREENTURTLE_DEAD_TAILTURNING;
		break;
	}
	default: {
		if (vx > 0) {
			aniID = ID_ANI_GREENTURTLE_WALK_RIGHT;
		}
		else aniID = ID_ANI_GREENTURTLE_WALK_LEFT;
		break;
	}
	}
	CAnimations::GetInstance()->Get(aniID)->Render(x, y);
	//RenderBoundingBox();
	check->Render();
}
