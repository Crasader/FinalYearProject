#pragma once

#include "cocos2d.h"
#include "GameScene.h"
#include "Tutorial.h"
#include "Export.h"
#include <algorithm>
#include <vector>
#include <string>

class TutorialInfo1 : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	cocos2d::Sprite *sprite;
	virtual bool init();

	// Called when main menu is selected 
	void activateTutorial(float dt);

	CREATE_FUNC(TutorialInfo1);
};