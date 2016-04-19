#include "TutorialInfo3.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* TutorialInfo3::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = TutorialInfo3::create();
	
	scene->addChild(layer);

	return scene;
}

void TutorialInfo3::activateTutorial(float dt)
{
	Director::getInstance()->popScene();
}

bool TutorialInfo3::init()
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
		Sprite::create("Tutorial/tutorialHeader3.png");
	loadingTitle->setPosition(Point(visibleSize.width / 2, (visibleSize.height - 85)));
	this->addChild(loadingTitle);

	auto tutorialInfo =
		Sprite::create("Tutorial/tutorial3.png");
	tutorialInfo->setPosition(Point(visibleSize.width /2 + 35, (visibleSize.height - 250)));
	this->addChild(tutorialInfo);

	this->scheduleOnce(schedule_selector(TutorialInfo3::activateTutorial), 3.5f);

	return true;
}