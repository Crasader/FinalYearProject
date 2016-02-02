#include "Police.h"

USING_NS_CC;

Police::Police(GameStates & gameState) :
m_gameState(gameState)
{
	
}

Police * Police::create(Vec2 position, GameStates & gameState)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();

	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile(ptr->m_textureAtlasPlistFile);		

	Police* pSprite = new Police(gameState);
	if (pSprite->initWithSpriteFrameName(ptr->m_police))
	{
		pSprite->autorelease();

		pSprite->initOptions(position);
		pSprite->setTag(70);
		cocos2d::Size size(80, 150);
		auto towerBody = PhysicsBody::createBox(size);
		towerBody->setCollisionBitmask(0x000002);
		towerBody->setTag(70);
		towerBody->setContactTestBitmask(true);
		//towerBody->setDynamic(false);

		pSprite->setPhysicsBody(towerBody);

		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

void Police::initOptions(Vec2 position)
{
	Point origin = Director::getInstance()->getVisibleOrigin();
	this->setPosition(position.x + origin.x, position.y + origin.y);
}
