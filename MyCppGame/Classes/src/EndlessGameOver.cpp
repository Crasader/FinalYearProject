#include "EndlessGameOver.h"

USING_NS_CC;

Scene* EndlessGameOver::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = EndlessGameOver::create();

	scene->addChild(layer);

	return scene;
}

void EndlessGameOver::activateGameScene(cocos2d::Ref *pSender)
{
	auto scene = Endless::createScene();
	Director::getInstance()->replaceScene(scene);
}

void EndlessGameOver::activateMainMenuScene(cocos2d::Ref *pSender)
{
	auto scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(scene);
}

bool EndlessGameOver::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backgroundSprite = Sprite::create("GameOverScreen/background.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(backgroundSprite);

	auto menuTitle =
		MenuItemImage::create("GameOverScreen/Game_Over.png",
			"GameOverScreen/Game_Over.png");
	auto retryItem =
		MenuItemImage::create("GameOverScreen/retrybutton.png",
			"GameOverScreen/retrybutton.png",
			CC_CALLBACK_1(EndlessGameOver::activateGameScene, this));
	auto mainMenuItem =
		MenuItemImage::create("GameOverScreen/mainmenubutton.png",
			"GameOverScreen/mainmenubutton.png",
			CC_CALLBACK_1(EndlessGameOver::activateMainMenuScene, this));
	auto menu = Menu::create(menuTitle, retryItem, mainMenuItem,
		NULL);

	menu->alignItemsVerticallyWithPadding(visibleSize.height / 10);
	this->addChild(menu);

	return true;
}