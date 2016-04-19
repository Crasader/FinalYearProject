#include "TutorialPauseScene.h"

USING_NS_CC;

Scene* TutorialPause::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = TutorialPause::create();

	scene->addChild(layer);

	return scene;
}

void TutorialPause::resume(Ref *pSender)
{
	Director::getInstance()->popScene();
}

void TutorialPause::activateMainMenuScene(Ref *pSender)
{
	auto scene = MainMenu::createScene();
	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(scene);
}

void TutorialPause::retry(Ref *pSender)
{
	auto scene = Tutorial::createScene();
	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(scene);
}

bool TutorialPause::init()
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
		Sprite::create("PauseScreen/Pauselogo.png");
	menuTitle->setPosition(Point(visibleSize.width / 2, (visibleSize.height - 40)));
	this->addChild(menuTitle);

	auto resumeItem =
		MenuItemImage::create("PauseScreen/resumebutton.png",
			"PauseScreen/resumebutton.png",
			CC_CALLBACK_1(TutorialPause::resume, this));
	auto retryItem =
		MenuItemImage::create("PauseScreen/retrybutton.png",
			"PauseScreen/retrybutton.png",
			CC_CALLBACK_1(TutorialPause::retry, this));
	auto mainMenuItem =
		MenuItemImage::create("PauseScreen/mainmenubutton.png",
			"PauseScreen/mainmenubutton.png",
			CC_CALLBACK_1(TutorialPause::activateMainMenuScene, this));
	auto menu = Menu::create(resumeItem, retryItem, mainMenuItem,
		NULL);
	/*auto menu = Menu::create(resumeItem, retryItem, mainMenuItem,
		NULL);*/
	resumeItem->setScale(1.25f);
	retryItem->setScale(1.25f);
	mainMenuItem->setScale(1.25f);
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 35);
	menu->setPosition(Point(visibleSize.width / 2, (visibleSize.height - 245)));
	this->addChild(menu);

	return true;
}