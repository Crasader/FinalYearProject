#include "Taxi.h"

USING_NS_CC;

Taxi::Taxi(GameStates & gameState) :
m_gameState(gameState)
{
	
}

Taxi * Taxi::create(Vec2 position, GameStates & gameState)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();

	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile(ptr->m_textureAtlasPlistFile);		

	Taxi* pSprite = new Taxi(gameState);
	if (pSprite->initWithSpriteFrameName(ptr->m_truck))
	{
		pSprite->autorelease();

		pSprite->initOptions(position);
		cocos2d::Size size(20, 100);
		auto towerBody = PhysicsBody::createBox(size);
		towerBody->setCollisionBitmask(0x000003);
		towerBody->setContactTestBitmask(true);
		//towerBody->setDynamic(false);

		pSprite->setPhysicsBody(towerBody);

		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

void Taxi::initOptions(Vec2 position)
{
	Point origin = Director::getInstance()->getVisibleOrigin();
	this->setPosition(position.x + origin.x, position.y + origin.y);
}
