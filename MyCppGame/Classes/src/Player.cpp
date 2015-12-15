#include "Player.h"

USING_NS_CC;

Player * Player::create()
{
	Player * player = new Player();
	if (player && player->initWithFile("GameScreen/Audi.png"))
	{
		player->autorelease();
		player->initPlayer();
		cocos2d::Size size(60, 120);
		auto playerBody = PhysicsBody::createBox(size);
		playerBody->setCollisionBitmask(0x000001);
		playerBody->setContactTestBitmask(true);
		playerBody->setDynamic(false);

		player->setPhysicsBody(playerBody);
		return player;
	}

	CC_SAFE_DELETE(player);
	return NULL;
}

void Player::initPlayer()
{

}