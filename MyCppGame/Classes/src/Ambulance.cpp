#include "Ambulance.h"

USING_NS_CC;

Ambulance::Ambulance(GameStates & gameState) :
m_gameState(gameState)
{
	
}

Ambulance * Ambulance::create(Vec2 position, GameStates & gameState)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();

	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile(ptr->m_textureAtlasPlistFile);		

	Ambulance* pSprite = new Ambulance(gameState);
	if (pSprite->initWithSpriteFrameName(ptr->m_ambulance))
	{
		pSprite->autorelease();

		pSprite->initOptions(position);
		cocos2d::Size size(60, 155);
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

void Ambulance::initOptions(Vec2 position)
{
	Point origin = Director::getInstance()->getVisibleOrigin();
	this->setPosition(position.x + origin.x, position.y + origin.y);
}
