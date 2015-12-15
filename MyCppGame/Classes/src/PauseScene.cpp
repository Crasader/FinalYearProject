#include "PauseScene.h"

USING_NS_CC;

Scene* PauseMenu::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = PauseMenu::create();

	scene->addChild(layer);

	return scene;
}

void PauseMenu::resume(Ref *pSender)
{
	Director::getInstance()->popScene();
}

void PauseMenu::activateMainMenuScene(Ref *pSender)
{
	auto scene = MainMenu::createScene();
	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(scene);
}

void PauseMenu::retry(Ref *pSender)
{
	auto scene = GameScreen::createScene();
	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(scene);
}

bool PauseMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backgroundSprite = Sprite::create("MainMenuScreen/background.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(backgroundSprite);

	auto resumeItem =
		MenuItemImage::create("PauseScreen/resumebutton.png",
			"PauseScreen/resumebutton.png",
			CC_CALLBACK_1(PauseMenu::resume, this));
	auto retryItem =
		MenuItemImage::create("PauseScreen/retrybutton.png",
			"PauseScreen/retrybutton.png",
			CC_CALLBACK_1(PauseMenu::retry, this));
	auto mainMenuItem =
		MenuItemImage::create("PauseScreen/mainmenubutton.png",
			"PauseScreen/mainmenubutton.png",
			CC_CALLBACK_1(PauseMenu::activateMainMenuScene, this));
	auto menu = Menu::create(resumeItem, retryItem, mainMenuItem,
		NULL);

	menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
	this->addChild(menu);

	return true;
}