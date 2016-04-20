#pragma once

#include "cocos2d.h"
#include "GameScene.h"
#include "Tutorial.h"

class ChooseMode : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();//creates the scene
	virtual bool init();
	// Called when retry is selected 
	void activateGameScene(Ref *pSender);//metohod that will change the scene to the gamescene
	// Called when main menu is selected 
	void activateTutorialScene(Ref *pSender);// method that will change the scene to the tutorial

	CREATE_FUNC(ChooseMode);
};