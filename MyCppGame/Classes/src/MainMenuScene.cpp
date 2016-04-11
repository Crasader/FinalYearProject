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
	//auto scene = Endless::createScene();
	//Director::getInstance()->replaceScene(scene);
	auto scene = GameScreen::createScene();
	Director::getInstance()->replaceScene(scene);
}

void MainMenu::activateOptionsScene(Ref *pSender)
{
	/*auto scene = Options::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));*/
	if (SonarCocosHelper::GooglePlayServices::isSignedIn)
	{
		SonarCocosHelper::GooglePlayServices::showAchievements();
	}
}

void MainMenu::activateQuitScene(Ref *pSender)
{
	//Director::getInstance()->end();
	if (SonarCocosHelper::GooglePlayServices::isSignedIn)
	{
		SonarCocosHelper::GooglePlayServices::showLeaderboard("CgkI69-MotMIEAIQAg");
	}
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
	menuTitle->setPosition(Point(visibleSize.width / 2 , (visibleSize.height - 30 )));
	this->addChild(menuTitle);

	auto playItem =
		MenuItemImage::create("MainMenuScreen/playbutton.png",
			"MainMenuScreen/playbutton.png",
			CC_CALLBACK_1(MainMenu::activateGameScene, this));
	auto optionsItem1 =
		MenuItemImage::create("MainMenuScreen/optionsbutton.png",
			"MainMenuScreen/optionsbutton.png",
			CC_CALLBACK_1(MainMenu::activateOptionsScene, this));
	auto quitItem1 =
		MenuItemImage::create("MainMenuScreen/quitbutton.png",
			"MainMenuScreen/quitbutton.png",
			CC_CALLBACK_1(MainMenu::activateQuitScene, this));
	auto optionsItem =
		MenuItemImage::create("MainMenuScreen/optionsbutton.png",
			"MainMenuScreen/optionsbutton.png",
			CC_CALLBACK_1(MainMenu::activateOptionsScene, this));
	auto quitItem =
		MenuItemImage::create("MainMenuScreen/quitbutton.png",
			"MainMenuScreen/quitbutton.png",
			CC_CALLBACK_1(MainMenu::activateQuitScene, this));
	//auto menu = Menu::create(menuTitle, playItem,optionsItem,quitItem, NULL);
	playItem->setScale(2.0f);
	optionsItem1->setScale(2.0f);
	quitItem1->setScale(2.0f);
	optionsItem->setScale(2.0f);
	quitItem->setScale(2.0f);
	auto menu = Menu::create(playItem, optionsItem, optionsItem1, quitItem1, quitItem, NULL);

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