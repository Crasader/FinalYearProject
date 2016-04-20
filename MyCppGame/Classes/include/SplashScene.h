#pragma once

#include "cocos2d.h"
#include "MainMenuScene.h"
#include "SonarFrameworks.h"

class Splash : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();//creates the scene.
	virtual bool init();
	// Called when main menu is selected 
	void activateMainMenuScene(float dt);//chenges the scene to the menu scene .

	CREATE_FUNC(Splash);
};