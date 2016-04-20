#pragma once

#include "cocos2d.h"
#include "GameScene.h"
#include "Level2.h"
#include "Level3.h"
#include "EndlessMode.h"
#include "OptionsScene.h"
#include "SonarFrameworks.h"
#include "ChooseModeScene.h"
#include "Tutorial.h"

class MainMenu : public cocos2d::Layer
{
public:
	cocos2d::Follow *camera;
	cocos2d::Sprite *cameraTarget;
	cocos2d::Sprite *backgroundSprite;//background sprites
	Size visibleSize;
	int y;//y varibale used to move the background sprite.
	void update(float dt);//update methid
	static cocos2d::Scene* createScene();// method used to create the menu scene
	virtual bool init();
	void activateGameScene(Ref * pSender);//changes the scene to the game scene
	void activateTrialScene(Ref *pSender);//changes the scene to the timetrial scene
	void activateTrophies(Ref *pSender);//changes the scene to the trophies scene using Google Play Services.
	void activateLeaderboards(Ref *pSender);//changes the scene to the leaderboards scene using Google Play Servies.
	void activateQuitScene(Ref *pSender);//closes the app.

	CREATE_FUNC(MainMenu);
};