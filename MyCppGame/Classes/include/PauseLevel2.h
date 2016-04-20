#pragma once

#include "cocos2d.h"
#include "EndlessMode.h"
#include "MainMenuScene.h"

class PauseLevel2 : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	// Called when resume is selected.
	void resume(Ref *pSender);//reumes the game when called.
	// Called when main menu is selected.
	void activateMainMenuScene(Ref *pSender);//changes the scene to the menu
	// Called when retry is selected.
	void retry(Ref *pSender);//restarts the game scene.
	void ToggleMusic(Ref *pSender);

	CREATE_FUNC(PauseLevel2);
};