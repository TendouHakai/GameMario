#pragma once

#define NODE_BBOX_WIDTH	16
#define NODE_BBOX_HEIGHT	16

#define NODEMAP_DONE	26001

#define NODEMAP_TYPE_SCENE	1

#define NODEMAP_STATE_DONE	100
class CNodeMap {
public:
	int type;
	float x, y;
	int sceneID;
	int nodeUPId;
	int nodeDOWNId;
	int nodeLEFTId;
	int nodeRIGHTId;

	CNodeMap(float x, float y, int left = -1, int right = -1 , int up = -1, int down = -1) {
		this->x = x;
		this->y = y;
		this->nodeUPId = up;
		this->nodeDOWNId = down;
		this->nodeLEFTId = left;
		this->nodeRIGHTId = right;
	}

};


typedef CNodeMap* LPNodeMap;

