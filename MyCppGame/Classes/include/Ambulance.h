#pragma once

#include "cocos2d.h"
#include "GameData.h"
#include "GameStates.h"

class Ambulance : public cocos2d::Sprite
{
private:
	GameStates & m_gameState;
public:
	Ambulance(GameStates & gameState);

	static Ambulance * create(cocos2d::Vec2 position, GameStates & gameState); //method for creating the ambulance with a sprite

	void initOptions(cocos2d::Vec2 position);

	void addEvents();
};