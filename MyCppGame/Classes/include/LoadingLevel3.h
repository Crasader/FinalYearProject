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
	static cocos2d::Scene* createScene();//method that creates the loading scene.
	cocos2d::Sprite *sprite;//loading sprites that is rotated.
	virtual bool init();
	void update(float dt);

	// Called when main menu is selected 
	void activateGameScene(float dt);//changes the scene to the game scene when called.

	CREATE_FUNC(LoadingLevel3);
};