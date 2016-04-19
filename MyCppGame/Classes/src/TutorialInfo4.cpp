#include "TutorialInfo4.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* TutorialInfo4::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = TutorialInfo4::create();
	
	scene->addChild(layer);

	return scene;
}

void TutorialInfo4::activateTutorial(float dt)
{
	Director::getInstance()->popScene();
}

bool TutorialInfo4::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backgroundSprite = Sprite::create("loadingBack.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(backgroundSprite);

	auto loadingTitle =
		Sprite::create("Tutorial/tutorialHeader4.png");
	loadingTitle->setPosition(Point(visibleSize.width / 2, (visibleSize.height/2) + origin.y));
	this->addChild(loadingTitle);

	this->scheduleOnce(schedule_selector(TutorialInfo4::activateTutorial), 3.5f);

	return true;
}