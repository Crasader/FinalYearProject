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

	static Coin * create(cocos2d::Vec2 position, GameStates & gameState);

	void initOptions(cocos2d::Vec2 position);

	void setPositionCoin();

	void addEvents();
};