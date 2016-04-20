#include "ChooseModeScene.h"

USING_NS_CC;

Scene* ChooseMode::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = ChooseMode::create();

	scene->addChild(layer);

	return scene;
}

void ChooseMode::activateGameScene(cocos2d::Ref *pSender)//plays the main game
{
	if (SonarCocosHelper::GooglePlayServices::isSignedIn)
	{
		SonarCocosHelper::GooglePlayServices::unlockAchievement("CgkI69-MotMIEAIQEQ");
	}
	auto scene = GameScreen::createScene();
	Director::getInstance()->replaceScene(scene);
}

void ChooseMode::activateTutorialScene(cocos2d::Ref *pSender)//plays the tutorial
{
	auto scene = Tutorial::createScene();
	Director::getInstance()->replaceScene(scene);
}

bool ChooseMode::init()
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
		Sprite::create("Tutorial/modeHeader.png");
	menuTitle->setPosition(Point(visibleSize.width / 2, (visibleSize.height - 32)));
	menuTitle->setScaleX(1.62f);
	menuTitle->setScaleY(1.3f);
	this->addChild(menuTitle);

	auto retryItem =
		MenuItemImage::create("MainMenuScreen/playbutton.png",
			"MainMenuScreen/playbutton.png",
			CC_CALLBACK_1(ChooseMode::activateGameScene, this));
	auto mainMenuItem =
		MenuItemImage::create("MainMenuScreen/tutorialbutton.png",
			"MainMenuScreen/tutorialbutton.png",
			CC_CALLBACK_1(ChooseMode::activateTutorialScene, this));
	auto menu = Menu::create(retryItem, mainMenuItem,
		NULL);

	//scales al the buttons in the scene
	retryItem->setScale(1.18f);
	mainMenuItem->setScale(1.18f);

	menu->alignItemsVerticallyWithPadding(visibleSize.height / 15);
	menu->setPosition(Point(visibleSize.width / 2, (visibleSize.height - 235)));
	this->addChild(menu);

	return true;
}