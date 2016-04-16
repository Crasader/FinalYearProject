#include "PowerUp.h"

USING_NS_CC;

PowerUp * PowerUp::create(int i)
{
	PowerUp * power = new PowerUp();
	if (i == 1)
	{
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
	}
	if (i == 2)
	{
		if (power && power->initWithFile("GameScreen/powerup1.png"))
		{
			power->autorelease();
			power->setTag(50);
			auto powerBody = PhysicsBody::createBox(power->getContentSize());
			powerBody->setCollisionBitmask(0x000004);
			powerBody->setContactTestBitmask(true);
			powerBody->setTag(50);

			power->setPhysicsBody(powerBody);
			return power;
		}
	}
	if (i == 3)
	{
		if (power && power->initWithFile("GameScreen/powerup2.png"))
		{
			power->autorelease();
			power->setTag(60);
			auto powerBody = PhysicsBody::createBox(power->getContentSize());
			powerBody->setCollisionBitmask(0x000004);
			powerBody->setContactTestBitmask(true);
			powerBody->setTag(60);

			power->setPhysicsBody(powerBody);
			return power;
		}
	}
	CC_SAFE_DELETE(power);
	return NULL;
}