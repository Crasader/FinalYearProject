#include "PowerUp.h"

USING_NS_CC;

PowerUp * PowerUp::create(int i)
{
	PowerUp * power = new PowerUp();
	if (power && power->initWithFile("GameScreen/powerup.png"))
	{
		power->autorelease();
		if (i == 1)
		{
			power->setTag(40);
		}
		else if (i == 2)
		{
			power->setTag(50);
		}
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