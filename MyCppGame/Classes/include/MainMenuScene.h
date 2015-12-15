#pragma once

#include "cocos2d.h"
#include "GameScene.h"
#include "OptionsScene.h"

class MainMenu : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void activateGameScene(Ref * pSender);
	void activateOptionsScene(Ref *pSender);
	void activateQuitScene(Ref *pSender);

	CREATE_FUNC(MainMenu);
};