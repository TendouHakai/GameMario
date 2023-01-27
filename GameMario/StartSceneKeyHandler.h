#pragma once
#include "SampleKeyEventHandler.h"
class StartSceneKeyHandler :
    public CSampleKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	StartSceneKeyHandler(LPSCENE s) :CSampleKeyHandler(s) {};
};

