#pragma once

#include "cocos2d.h"
#include "GameData.h"
#include "GameStates.h"

class Coin : public cocos2d::Sprite
{
private:
	GameStates & m_gameState;
public:
	Coin(GameStates & gameState);

	static Coin * create(cocos2d::Vec2 position, GameStates & gameState);//method used to create the coin and setting the image we use

	void initOptions(cocos2d::Vec2 position);//sets the position the coin will be placed at

	void setPositionCoin();

	void addEvents();
};