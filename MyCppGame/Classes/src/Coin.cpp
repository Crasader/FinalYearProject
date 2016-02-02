#include "Coin.h"

USING_NS_CC;

Coin::Coin(GameStates & gameState) :
m_gameState(gameState)
{
	
}

Coin * Coin::create(Vec2 position, GameStates & gameState)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();

	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile(ptr->m_textureAtlasPlistFile);		

	Coin* pSprite = new Coin(gameState);
	if (pSprite->initWithSpriteFrameName(ptr->m_coinFile))
	{
		pSprite->autorelease();

		pSprite->initOptions(position);

		pSprite->addEvents();
		pSprite->setTag(30);

		auto towerBody = PhysicsBody::createBox(pSprite->getContentSize());
		towerBody->setCollisionBitmask(0x000003);
		towerBody->setContactTestBitmask(true);
		towerBody->setTag(30);
		//towerBody->setDynamic(false);

		pSprite->setPhysicsBody(towerBody);

		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

void Coin::initOptions(Vec2 position)
{
	Point origin = Director::getInstance()->getVisibleOrigin();
	this->setPosition(position.x + origin.x, position.y + origin.y);
}

void Coin::addEvents()
{
	//auto listener = cocos2d::EventListenerTouchOneByOne::create();
	//listener->setSwallowTouches(true);

	//listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
	//{
	//	cocos2d::Vec2 pos = touch->getLocation();
	//	cocos2d::Rect rect = this->getBoundingBox();

	//	if (rect.containsPoint(pos))
	//	{
	//		return true; // to indicate that we have consumed it.
	//	}

	//	return false; // we did not consume this event, pass through.
	//};

	//listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	//{
	//	handleTouchEvent(touch);
	//};

	//cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
}