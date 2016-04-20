#pragma once

#include "cocos2d.h"
#include "GameScene.h"
#include "MainMenuScene.h"

class GameOver : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();//creates the game over scene
	virtual bool init();
	// Called when retry is selected 
	void activateGameScene(Ref *pSender);//method that changes the current scene to the game scene
	// Called when main menu is selected 
	void activateMainMenuScene(Ref *pSender);//method that changes the current scene to the menu scene

	CREATE_FUNC(GameOver);
};