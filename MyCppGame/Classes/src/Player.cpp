#include "Player.h"

USING_NS_CC;

Player * Player::create()
{
	Player * player = new Player();
	if (player && player->initWithFile("GameScreen/Audi1.png"))
	{
		player->autorelease();
		player->initPlayer();
		player->setTag(10);//sets the tag for the object
		cocos2d::Size size(70, 155);
		auto playerBody = PhysicsBody::createBox(size);//sets tge size of the physics body
		playerBody->setCollisionBitmask(0x000001);
		playerBody->setTag(10);//sets the tag for the object
		playerBody->setContactTestBitmask(true);
		playerBody->setDynamic(false);

		player->setPhysicsBody(playerBody);//applys the physics body to the sprites
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
}