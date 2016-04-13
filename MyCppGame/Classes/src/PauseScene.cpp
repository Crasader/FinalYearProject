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
	//if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	//{
	//	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	//}
	//else
	//	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/background.mp3", true);
	
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
	resumeItem->setScale(1.1f);
	retryItem->setScale(1.1f);
	mainMenuItem->setScale(1.1f);
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 15);
	menu->setPosition(Point(visibleSize.width / 2, (visibleSize.height - 245)));
	this->addChild(menu);

	return true;
}