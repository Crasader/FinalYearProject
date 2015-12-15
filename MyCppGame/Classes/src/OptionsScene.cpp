#include "OptionsScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* Options::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = Options::create();

	scene->addChild(layer);

	return scene;
}

void Options::activateMainMenuScene(cocos2d::Ref *pSender)
{
	auto scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(scene);
}

bool Options::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backgroundSprite = Sprite::create("optionsbackground.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(backgroundSprite);

	auto mainMenuItem =
		MenuItemImage::create("backbutton.png",
			"backbutton.png",
			CC_CALLBACK_1(Options::activateMainMenuScene, this));
	auto menu = Menu::create( mainMenuItem,NULL);

	menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
	this->addChild(menu);

	return true;
}