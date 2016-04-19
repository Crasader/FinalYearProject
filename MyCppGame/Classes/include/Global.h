#pragma once

#include "cocos2d.h"

class Global
{
private:
	Global();
	int scoreValue;

public:
	static Global* getInstance();
	int getScore();
	void setScore(int s);
	void resetScore();

	//_SYNTHESIZE(int, scoreValue, ScoreValue);
};