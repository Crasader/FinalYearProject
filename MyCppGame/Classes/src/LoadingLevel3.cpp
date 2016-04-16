#include "LoadingLevel3.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* LoadingLevel3::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = LoadingLevel3::create();
	
	scene->addChild(layer);

	return scene;
}

void LoadingLevel3::activateGameScene(float dt)
{
	auto scene = Level3::createScene();
	Director::getInstance()->replaceScene(scene);
}

bool LoadingLevel3::init()
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

	this->scheduleOnce(schedule_selector(LoadingLevel3::activateGameScene), 2.0f);

	this->scheduleUpdate();
	return true;
}

void LoadingLevel3::update(float dt)
{
	sprite->setRotation(sprite->getRotation() + 5.0f);
}