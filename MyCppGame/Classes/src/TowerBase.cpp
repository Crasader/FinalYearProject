#include "TowerBase.h"

USING_NS_CC;

TowerBase::TowerBase(GameStates & gameState) : 
m_gameState(gameState),
m_touched(false)
{
	
}

TowerBase * TowerBase::create(Vec2 position, GameStates & gameState)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();

	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile(ptr->m_textureAtlasPlistFile);		

	TowerBase* pSprite = new TowerBase(gameState);
	if (pSprite->initWithSpriteFrameName(ptr->m_taxi))
	{
		pSprite->autorelease();

		pSprite->initOptions(position);

		pSprite->addEvents();

		auto towerBody = PhysicsBody::createBox(pSprite->getContentSize());
		towerBody->setCollisionBitmask(0x000002);
		towerBody->setContactTestBitmask(true);
		towerBody->setDynamic(false);

		pSprite->setPhysicsBody(towerBody);

		pSprite->addBody(pSprite);

		return pSprite;
	}

	//auto towerBody = PhysicsBody::createBox(pSprite->getContentSize());
	//towerBody->setCollisionBitmask(0x000002);
	//towerBody->setContactTestBitmask(true);
	//towerBody->setDynamic(false);

	//pSprite->setPhysicsBody(towerBody);

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

void TowerBase::initOptions(Vec2 position)
{
	Point origin = Director::getInstance()->getVisibleOrigin();
	this->setPosition(position.x + origin.x, position.y + origin.y);
}

void TowerBase::addEvents()
{

}

void TowerBase::addBody(TowerBase * sprite)
{
	auto towerBody = PhysicsBody::createBox(sprite->getContentSize());
	towerBody->setCollisionBitmask(0x000002);
	towerBody->setContactTestBitmask(true);

	sprite->setPhysicsBody(towerBody);
}

void TowerBase::handleTouchEvent(cocos2d::Touch* touch)
{
	// Change gameState in response to sprite touched
	m_gameState = GameStates::GameInit;
	m_touched = true;
}

bool TowerBase::isTouched() const
{
	return m_touched;
}
