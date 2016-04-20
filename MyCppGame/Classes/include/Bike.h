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

	static Bike * create(cocos2d::Vec2 position, GameStates & gameState);//method used to create bike object and setting the image to be used

	void initOptions(cocos2d::Vec2 position);//method for setting the position we want the image to be

	void addEvents();
};