#include "Bike.h"

USING_NS_CC;

Bike::Bike(GameStates & gameState) :
m_gameState(gameState)
{
	
}

Bike * Bike::create(Vec2 position, GameStates & gameState)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();

	auto spritecache = SpriteFrameCache::getInstance();	

	Bike* pSprite = new Bike(gameState);
	if (pSprite && pSprite->initWithFile("GameScreen/bikepic.png"))
	{
		pSprite->autorelease();

		pSprite->initOptions(position);
		cocos2d::Size size(60, 150);
		auto towerBody = PhysicsBody::createBox(size);
		towerBody->setCollisionBitmask(0x000002);
		towerBody->setContactTestBitmask(true);

		pSprite->setPhysicsBody(towerBody);

		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

void Bike::initOptions(Vec2 position)
{
	Point origin = Director::getInstance()->getVisibleOrigin();
	this->setPosition(position.x + origin.x, position.y + origin.y);
}
