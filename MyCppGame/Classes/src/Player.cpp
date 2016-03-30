#include "Player.h"

USING_NS_CC;

Player * Player::create()
{
	Player * player = new Player();
	if (player && player->initWithFile("GameScreen/Audi.png"))
	{
		player->autorelease();
		player->initPlayer();
		player->setTag(10);
		cocos2d::Size size(70, 150);
		auto playerBody = PhysicsBody::createBox(size);
		playerBody->setCollisionBitmask(0x000001);
		playerBody->setTag(10);
		playerBody->setContactTestBitmask(true);
		playerBody->setDynamic(false);

		//player->setPhysicsBody(playerBody);
		return player;
	}

	CC_SAFE_DELETE(player);
	return NULL;
}

void Player::initPlayer()
{

}

void Player::createBody(Player * p)
{
	//cocos2d::Size size(70, 150);
	//auto playerBody = PhysicsBody::createBox(size);
	//playerBody->setCollisionBitmask(0x000001);
	//playerBody->setTag(10);
	//playerBody->setContactTestBitmask(true);
	//playerBody->setDynamic(false);

	//p->setPhysicsBody(playerBody);
}