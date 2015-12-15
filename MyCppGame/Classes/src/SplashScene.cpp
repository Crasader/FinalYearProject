#include "SplashScene.h"
#include "ui/CocosGUI.h"


#define DISPLAY_SPALSH_SCENE 2

USING_NS_CC;

Scene* Splash::createScene()
{
	auto scene = Scene::create();
	auto layer = Splash::create();

	scene->addChild(layer);

	return scene;
}

void Splash::activateMainMenuScene(float dt)
{
	auto scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(scene);
}

bool Splash::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backgroundSprite = Sprite::create("splashbackground.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(backgroundSprite);

	auto logo = Sprite::create("logo.jpeg");
	logo->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(logo);

	this->scheduleOnce(schedule_selector(Splash::activateMainMenuScene), 4.0f);

	return true;
}