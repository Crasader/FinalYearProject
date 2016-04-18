#include "GameCompleteScene.h"

USING_NS_CC;

Scene* GameComplete::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = GameComplete::create();

	scene->addChild(layer);

	return scene;
}

void GameComplete::activateGameScene(cocos2d::Ref *pSender)
{
	auto scene = GameScreen::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameComplete::activateMainMenuScene(cocos2d::Ref *pSender)
{
	auto scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(scene);
}

bool GameComplete::init()
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
		Sprite::create("GameOverScreen/gameCompleted.png");
	menuTitle->setPosition(Point(visibleSize.width / 2, (visibleSize.height - 32)));
	this->addChild(menuTitle);

	auto retryItem =
		MenuItemImage::create("GameOverScreen/retrybutton.png",
			"GameOverScreen/retrybutton.png",
			CC_CALLBACK_1(GameComplete::activateGameScene, this));
	auto mainMenuItem =
		MenuItemImage::create("GameOverScreen/mainmenubutton.png",
			"GameOverScreen/mainmenubutton.png",
			CC_CALLBACK_1(GameComplete::activateMainMenuScene, this));
	auto menu = Menu::create(retryItem, mainMenuItem,
		NULL);
	retryItem->setScale(1.18f);
	mainMenuItem->setScale(1.18f);
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 15);
	menu->setPosition(Point(visibleSize.width / 2, (visibleSize.height - 235)));
	this->addChild(menu);

	return true;
}