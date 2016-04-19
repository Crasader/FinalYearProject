#include "TutorialInfo1.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* TutorialInfo1::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = TutorialInfo1::create();
	
	scene->addChild(layer);

	return scene;
}

void TutorialInfo1::activateTutorial(float dt)
{
	//auto scene = Tutorial::createScene();
	//Director::getInstance()->replaceScene(scene);
	Director::getInstance()->popScene();
}

bool TutorialInfo1::init()
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
		Sprite::create("Tutorial/tutorialHeader1.png");
	loadingTitle->setPosition(Point(visibleSize.width / 2, (visibleSize.height - 38)));
	this->addChild(loadingTitle);

	sprite = Sprite::create("Tutorial/tutorial1.png");
	sprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height - 285));
	sprite->setScale(0.75);
	this->addChild(sprite);

	this->scheduleOnce(schedule_selector(TutorialInfo1::activateTutorial), 3.5f);

	return true;
}