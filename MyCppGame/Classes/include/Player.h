#pragma once

#include "cocos2d.h"

class Player : public cocos2d::Sprite
{
public:
	static Player * create(void);// creates the player object.
	void createBody(Player * p);//creates the physics body 

private:
	void initPlayer();

	//CREATE_FUNC(Player);
};
