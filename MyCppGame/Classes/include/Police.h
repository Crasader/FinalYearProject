#pragma once

#include "cocos2d.h"
#include "GameData.h"
#include "GameStates.h"

class Police : public cocos2d::Sprite
{
private:
	GameStates & m_gameState;
public:
	Police(GameStates & gameState);

	static Police * create(cocos2d::Vec2 position, GameStates & gameState);//creates the object.

	void initOptions(cocos2d::Vec2 position);//sets the position for the image.

	void addEvents();
};