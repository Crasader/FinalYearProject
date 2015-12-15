#pragma once

#include "cocos2d.h"

class HUD : public cocos2d::Sprite
{
public:
	static HUD * create(void);

private:
	void initHUD();
};
