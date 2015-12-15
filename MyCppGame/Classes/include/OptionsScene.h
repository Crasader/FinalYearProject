#pragma once

#include "cocos2d.h"
#include "MainMenuScene.h"

class Options : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	// Called when main menu is selected 
	void activateMainMenuScene(Ref *pSender);

	CREATE_FUNC(Options);
};