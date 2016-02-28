#pragma once

#include "cocos2d.h"
#include "MainMenuScene.h"
#include "SonarFrameworks.h"

class Splash : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	// Called when main menu is selected 
	void activateMainMenuScene(float dt);

	CREATE_FUNC(Splash);
};