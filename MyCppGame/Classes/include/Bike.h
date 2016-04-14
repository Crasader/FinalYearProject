#pragma once

#include "cocos2d.h"
#include "GameData.h"
#include "GameStates.h"

class Bike : public cocos2d::Sprite
{
private:
	GameStates & m_gameState;
public:
	Bike(GameStates & gameState);

	static Bike * create(cocos2d::Vec2 position, GameStates & gameState);

	void initOptions(cocos2d::Vec2 position);

	void addEvents();
};