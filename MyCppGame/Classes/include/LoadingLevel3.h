#pragma once

#include "cocos2d.h"
#include "GameScene.h"
#include "Level3.h"
#include "Export.h"
#include <algorithm>
#include <vector>
#include <string>

class LoadingLevel3 : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	cocos2d::Sprite *sprite;
	virtual bool init();
	void update(float dt);

	// Called when main menu is selected 
	void activateGameScene(float dt);

	CREATE_FUNC(LoadingLevel3);
};