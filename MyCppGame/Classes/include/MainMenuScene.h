#pragma once

#include "cocos2d.h"
#include "GameScene.h"
#include "Level2.h"
#include "EndlessMode.h"
#include "OptionsScene.h"
#include "SonarFrameworks.h"

class MainMenu : public cocos2d::Layer
{
public:
	cocos2d::Follow *camera;
	cocos2d::Sprite *cameraTarget;
	cocos2d::Sprite *backgroundSprite;
	Size visibleSize;
	int y;
	void update(float dt);
	static cocos2d::Scene* createScene();
	virtual bool init();
	void activateGameScene(Ref * pSender);
	void activateTrialScene(Ref *pSender);
	void activateTrophies(Ref *pSender);
	void activateLeaderboards(Ref *pSender);
	void activateQuitScene(Ref *pSender);

	CREATE_FUNC(MainMenu);
};