#pragma once

#include "cocos2d.h"

class Player : public cocos2d::Sprite
{
public:
	static Player * create(void);

private:
	void initPlayer();

	//CREATE_FUNC(Player);
};
