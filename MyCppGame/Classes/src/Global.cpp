#include "Global.h"

USING_NS_CC;

static Global* global = nullptr;

Global::Global()
{
	scoreValue = 0;
}

Global* Global::getInstance()
{
	if (!global) {
		global = new (std::nothrow)Global();
	}

	return global;
}

void Global::setScore(int s)
{
	scoreValue = scoreValue + s;
}
int Global::getScore()
{
	return scoreValue;
}