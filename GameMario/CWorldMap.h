#pragma once

#define NODE_BBOX_WIDTH	16
#define NODE_BBOX_HEIGHT	16

#define NODEMAP_DONE	26001

#define NODEMAP_STATE_DONE	100
#define NODEMAP_STATE_NOTDONE	200

#define NODEMAP_TYPE_START	1
#define NODEMAP_TYPE_MISSION	2
#define NODEMAP_TYPE_STEP	3
class CNodeMap {
public:
	int status;
	int type;
	float x, y;
	int sceneID;
	int nodeUPId;
	int nodeDOWNId;
	int nodeLEFTId;
	int nodeRIGHTId;

	CNodeMap(float x, float y, int left = -1, int right = -1 , int up = -1, int down = -1, int idscene = -1, int type = NODEMAP_TYPE_STEP) {
		this->x = x;
		this->y = y;
		this->nodeUPId = up;
		this->nodeDOWNId = down;
		this->nodeLEFTId = left;
		this->nodeRIGHTId = right;
		this->sceneID = idscene;
		this->type = type;

		this->status = NODEMAP_STATE_NOTDONE;
	}

	void setDone() {
		this->status = NODEMAP_STATE_DONE;
	}
};

typedef CNodeMap* LPNodeMap;

