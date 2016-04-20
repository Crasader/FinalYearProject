#pragma once

#include "cocos2d.h"
#include "GameScene.h"
#include "MainMenuScene.h"

class TutorialOver : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	// Called when retry is selected 
	void activateGameScene(Ref *pSender);//changes scene to game scene.
	// Called when main menu is selected 
	void activateMainMenuScene(Ref *pSender);//changes scene to main menu scene.

	CREATE_FUNC(TutorialOver);
};