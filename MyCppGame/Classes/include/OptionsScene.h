#pragma once

#include "cocos2d.h"
#include "MainMenuScene.h"

class Options : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();//creates the scene.
	virtual bool init();

	// Called when main menu is selected 
	void activateMainMenuScene(Ref *pSender);//changes the current scene to the main menu scene.

	CREATE_FUNC(Options);
};