#pragma once
#include "Scene.h"
class IntroKeyEventHandler :
    public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	IntroKeyEventHandler(LPSCENE s) :CSceneKeyHandler(s) {};
};

