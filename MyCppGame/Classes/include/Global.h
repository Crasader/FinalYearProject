#pragma once

#include "cocos2d.h"

class Global
{
private:
	Global();
	int scoreValue;//score variable used the the main game mode.

public:
	static Global* getInstance();
	int getScore();//returns the score variable
	void setScore(int s);//adds whatever is passed in to the score variable
	void resetScore();//resets the score variable to zero.
};