#pragma once

#include "cocos2d.h"

class Player : public cocos2d::Sprite
{
public:
	static Player * create(void);
	void createBody(Player * p);

private:
	void initPlayer();

	//CREATE_FUNC(Player);
};
