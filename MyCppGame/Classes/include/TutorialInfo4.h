#pragma once

#include "cocos2d.h"
#include "GameScene.h"
#include "Tutorial.h"
#include "Export.h"
#include <algorithm>
#include <vector>
#include <string>

class TutorialInfo4 : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	cocos2d::Sprite *sprite;//sprite that displays info on crashing into cars.
	virtual bool init();

	// Called when main menu is selected 
	void activateTutorial(float dt);//resumes the tutorial when called.

	CREATE_FUNC(TutorialInfo4);
};