#include "PowerUp.h"

USING_NS_CC;

PowerUp * PowerUp::create(int i)
{
	PowerUp * power = new PowerUp();
	if (i == 1)//checks to see if its an invisibility power up
	{
		if (power && power->initWithFile("GameScreen/powerup.png"))
		{
			power->autorelease();
			power->setTag(40); //sets its tag
			auto powerBody = PhysicsBody::createBox(power->getContentSize());//sets the size of the physics body to the size of the image
			powerBody->setCollisionBitmask(0x000004);
			powerBody->setContactTestBitmask(true);
			powerBody->setTag(40); //sets its tag

			power->setPhysicsBody(powerBody);//applys the physics body to the object
			return power;
		}
	}
	if (i == 2)//checks to see if its an speed boost power up
	{
		if (power && power->initWithFile("GameScreen/powerup1.png"))
		{
			power->autorelease();
			power->setTag(50); //sets its tag
			auto powerBody = PhysicsBody::createBox(power->getContentSize());//sets the size of the physics body to the size of the image
			powerBody->setCollisionBitmask(0x000004);
			powerBody->setContactTestBitmask(true);
			powerBody->setTag(50); //sets its tag

			power->setPhysicsBody(powerBody);//applys the physics body to the object
			return power;
		}
	}
	if (i == 3)//checks to see if its an score boost power up
	{
		if (power && power->initWithFile("GameScreen/powerup2.png"))
		{
			power->autorelease();
			power->setTag(60); //sets its tag
			auto powerBody = PhysicsBody::createBox(power->getContentSize());//sets the size of the physics body to the size of the image
			powerBody->setCollisionBitmask(0x000004);
			powerBody->setContactTestBitmask(true);
			powerBody->setTag(60); //sets its tag

			power->setPhysicsBody(powerBody);//applys the physics body to the object
			return power;
		}
	}
	CC_SAFE_DELETE(power);
	return NULL;
}