#include "PauseLevel2.h"

USING_NS_CC;

Scene* PauseLevel2::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = PauseLevel2::create();

	scene->addChild(layer);

	return scene;
}

void PauseLevel2::resume(Ref *pSender)
{
	Director::getInstance()->popScene();
}

void PauseLevel2::ToggleMusic(Ref *pSender)
{
	if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		if (SonarCocosHelper::GooglePlayServices::isSignedIn)
		{
			SonarCocosHelper::GooglePlayServices::unlockAchievement("CgkI69-MotMIEAIQEg");
		}
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
	else
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/background.mp3", true);
}

void PauseLevel2::activateMainMenuScene(Ref *pSender)
{
	auto scene = MainMenu::createScene();
	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(scene);
}

void PauseLevel2::retry(Ref *pSender)
{
	auto scene = Endless::createScene();
	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(scene);
}

bool PauseLevel2::init()
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
			CC_CALLBACK_1(PauseLevel2::resume, this));
	auto retryItem =
		MenuItemImage::create("PauseScreen/retrybutton.png",
			"PauseScreen/retrybutton.png",
			CC_CALLBACK_1(PauseLevel2::retry, this));
	auto musicItem =
		MenuItemImage::create("PauseScreen/musicbutton.png",
			"PauseScreen/musicbutton.png",
			CC_CALLBACK_1(PauseLevel2::ToggleMusic, this));
	auto mainMenuItem =
		MenuItemImage::create("PauseScreen/mainmenubutton.png",
			"PauseScreen/mainmenubutton.png",
			CC_CALLBACK_1(PauseLevel2::activateMainMenuScene, this));
	auto menu = Menu::create(resumeItem, retryItem, musicItem, mainMenuItem,
		NULL);
	
	resumeItem->setScale(1.25f);
	retryItem->setScale(1.25f);
	musicItem->setScale(1.25f);
	mainMenuItem->setScale(1.25f);
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 35);
	menu->setPosition(Point(visibleSize.width / 2, (visibleSize.height - 245)));
	this->addChild(menu);

	return true;
}