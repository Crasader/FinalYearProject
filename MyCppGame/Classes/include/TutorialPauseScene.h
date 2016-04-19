#pragma once

#include "cocos2d.h"
#include "Tutorial.h"
#include "MainMenuScene.h"

class TutorialPause : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	// Called when resume is selected.
	void resume(Ref *pSender);
	// Called when main menu is selected.
	void activateMainMenuScene(Ref *pSender);
	// Called when retry is selected.
	void retry(Ref *pSender);

	CREATE_FUNC(TutorialPause);
};