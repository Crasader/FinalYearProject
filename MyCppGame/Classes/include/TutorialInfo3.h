#pragma once

#include "cocos2d.h"
#include "GameScene.h"
#include "Tutorial.h"
#include "Export.h"
#include <algorithm>
#include <vector>
#include <string>

class TutorialInfo3 : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	cocos2d::Sprite *sprite;//sprites that displays info about power ups.
	virtual bool init();

	// Called when main menu is selected 
	void activateTutorial(float dt);//changes scene back to tutorial.

	CREATE_FUNC(TutorialInfo3);
};