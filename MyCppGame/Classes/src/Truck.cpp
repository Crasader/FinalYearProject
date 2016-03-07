#include "Truck.h"

USING_NS_CC;

Truck::Truck(GameStates & gameState) :
m_gameState(gameState)
{
	
}

Truck * Truck::create(Vec2 position, GameStates & gameState)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();

	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile(ptr->m_textureAtlasPlistFile);		

	Truck* pSprite = new Truck(gameState);
	if (pSprite->initWithSpriteFrameName(ptr->m_truck))
	{
		pSprite->autorelease();

		pSprite->initOptions(position);

		cocos2d::Size size(70, 200);
		auto towerBody = PhysicsBody::createBox(size);
		towerBody->setCollisionBitmask(0x000002);
		towerBody->setContactTestBitmask(true);
		//towerBody->setDynamic(false);

		pSprite->setPhysicsBody(towerBody);

		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

void Truck::initOptions(Vec2 position)
{
	Point origin = Director::getInstance()->getVisibleOrigin();
	this->setPosition(position.x + origin.x, position.y + origin.y);
}
