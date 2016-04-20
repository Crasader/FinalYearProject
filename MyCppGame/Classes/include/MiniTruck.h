#pragma once

#include "cocos2d.h"
#include "GameData.h"
#include "GameStates.h"

class MiniTruck : public cocos2d::Sprite
{
private:
	GameStates & m_gameState;
public:
	MiniTruck(GameStates & gameState);

	static MiniTruck * create(cocos2d::Vec2 position, GameStates & gameState);//creates the object 

	void initOptions(cocos2d::Vec2 position);//sets the position where the obect is going to be drawn.

	void addEvents();
};