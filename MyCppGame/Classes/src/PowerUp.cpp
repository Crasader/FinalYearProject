#include "PowerUp.h"

USING_NS_CC;

PowerUp * PowerUp::create()
{
	PowerUp * power = new PowerUp();
	if (power && power->initWithFile("GameScreen/powerup.png"))
	{
		power->autorelease();
		power->setTag(40);
		auto powerBody = PhysicsBody::createBox(power->getContentSize());
		powerBody->setCollisionBitmask(0x000004);
		powerBody->setContactTestBitmask(true);
		powerBody->setTag(40);

		power->setPhysicsBody(powerBody);
		return power;
	}

	CC_SAFE_DELETE(power);
	return NULL;
}