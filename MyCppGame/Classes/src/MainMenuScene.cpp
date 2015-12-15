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

void MainMenu::activateOptionsScene(Ref *pSender)
{
	auto scene = Options::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));
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
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backgroundSprite = Sprite::create("MainMenuScreen/background.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(backgroundSprite);

	auto menuTitle =
		MenuItemImage::create("MainMenuScreen/title.png",
			"MainMenuScreen/title.png");
	auto playItem =
		MenuItemImage::create("MainMenuScreen/playbutton.png",
			"MainMenuScreen/playbutton.png",
			CC_CALLBACK_1(MainMenu::activateGameScene, this));
	auto optionsItem =
		MenuItemImage::create("MainMenuScreen/optionsbutton.png",
			"MainMenuScreen/optionsbutton.png",
			CC_CALLBACK_1(MainMenu::activateOptionsScene, this));
	auto quitItem =
		MenuItemImage::create("MainMenuScreen/quitbutton.png",
			"MainMenuScreen/quitbutton.png",
			CC_CALLBACK_1(MainMenu::activateQuitScene, this));
	auto menu = Menu::create(menuTitle, playItem,optionsItem,quitItem, NULL);

	// Returns visible size of OpenGL window in points.
	//Size visibleSize = Director::getInstance()->getVisibleSize();
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 15);
	this->addChild(menu);

	return true;
}