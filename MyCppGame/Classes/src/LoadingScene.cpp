#include "LoadingScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* Loading::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = Loading::create();
	
	scene->addChild(layer);

	return scene;
}

void Loading::activateGameScene(float dt)
{
	auto scene = Level2::createScene();
	Director::getInstance()->replaceScene(scene);
}

bool Loading::init()
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

	sprite = Sprite::create("Loading.png");
	sprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(sprite);

	this->scheduleOnce(schedule_selector(Loading::activateGameScene), 2.0f);

	this->scheduleUpdate();
	return true;
}

void Loading::update(float dt)
{
	sprite->setRotation(sprite->getRotation() + 5.0f);
}