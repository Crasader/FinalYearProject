#include "MainMenuScene.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = MainMenu::create();

	scene->addChild(layer);

	return scene;
}

void MainMenu::activateGameScene(Ref *pSender)
{
	auto scene = GameScreen::createScene();
	Director::getInstance()->replaceScene(scene);
}

void MainMenu::activateTrialScene(Ref *pSender)
{
	auto scene = Endless::createScene();
	Director::getInstance()->replaceScene(scene);
}

void MainMenu::activateTrophies(Ref *pSender)
{
	if (SonarCocosHelper::GooglePlayServices::isSignedIn)
	{
		SonarCocosHelper::GooglePlayServices::showAchievements();
	}
}

void MainMenu::activateLeaderboards(Ref *pSender)
{
	if (SonarCocosHelper::GooglePlayServices::isSignedIn)
	{
		SonarCocosHelper::GooglePlayServices::showLeaderboard("CgkI69-MotMIEAIQAg");
	}
}

void MainMenu::activateQuitScene(Ref *pSender)
{
	Director::getInstance()->end();
}

bool MainMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	backgroundSprite = Sprite::create("GameScreen/roadbackground.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, (visibleSize.height) + 500));
	y = (visibleSize.height) + 500;
	this->addChild(backgroundSprite);

	/*auto menuTitle =
		MenuItemImage::create("MainMenuScreen/horizonlogo.png",
			"MainMenuScreen/horizonlogo.png");*/
	auto menuTitle =
		Sprite::create("MainMenuScreen/horizonlogo.png");
	menuTitle->setPosition(Point(visibleSize.width / 2 , (visibleSize.height - 20 )));
	this->addChild(menuTitle);

	auto playItem =
		MenuItemImage::create("MainMenuScreen/playbutton.png",
			"MainMenuScreen/playbutton.png",
			CC_CALLBACK_1(MainMenu::activateGameScene, this));
	auto optionsItem1 =
		MenuItemImage::create("MainMenuScreen/timebutton.png",
			"MainMenuScreen/timebutton.png",
			CC_CALLBACK_1(MainMenu::activateTrialScene, this));
	auto quitItem1 =
		MenuItemImage::create("MainMenuScreen/leadbutton.png",
			"MainMenuScreen/leadbutton.png",
			CC_CALLBACK_1(MainMenu::activateLeaderboards, this));
	auto optionsItem =
		MenuItemImage::create("MainMenuScreen/trophybutton.png",
			"MainMenuScreen/trophybutton.png",
			CC_CALLBACK_1(MainMenu::activateTrophies, this));
	auto quitItem =
		MenuItemImage::create("MainMenuScreen/quitbutton.png",
			"MainMenuScreen/quitbutton.png",
			CC_CALLBACK_1(MainMenu::activateQuitScene, this));
	//auto menu = Menu::create(menuTitle, playItem,optionsItem,quitItem, NULL);
	playItem->setScale(1.28f);
	optionsItem1->setScale(1.28f);
	quitItem1->setScale(1.28f);
	optionsItem->setScale(1.28f);
	quitItem->setScale(1.28f);
	auto menu = Menu::create(playItem, optionsItem1, optionsItem, quitItem1, quitItem, NULL);

	// Returns visible size of OpenGL window in points.
	//Size visibleSize = Director::getInstance()->getVisibleSize();
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 15);
	menu->setPosition(Point(visibleSize.width / 2, (visibleSize.height - 282)));
	this->addChild(menu);

	//cameraTarget = Sprite::create();
	//cameraTarget->setPositionX(visibleSize.width / 2);
	//cameraTarget->setPositionY(y);
	this->scheduleUpdate();
	//this->addChild(cameraTarget);
	//camera = Follow::create(cameraTarget, Rect::ZERO);
	//camera->retain();
	//this->runAction(camera);

	return true;
}

void MainMenu::update(float dt)
{
	y = y - 5;
	backgroundSprite->setPosition(backgroundSprite->getPosition().x, y);

	if (y < -530)
	{
		y = (visibleSize.height) + 500;
	}
}