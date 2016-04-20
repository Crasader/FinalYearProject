#pragma once

#include "cocos2d.h"

class HUD : public cocos2d::Sprite
{
public:
	static HUD * create(void);//method that creates the HUD object and sets the image.

private:
	void initHUD();
};
