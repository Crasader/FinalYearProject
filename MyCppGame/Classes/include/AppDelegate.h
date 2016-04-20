#pragma once

#include "cocos2d.h"
#include "LevelLoader.h"

class  AppDelegate : private cocos2d::Application
{
private: // Add  this
	std::shared_ptr<GameData> m_ptr;

public:
	AppDelegate();
	virtual ~AppDelegate();
	virtual bool applicationDidFinishLaunching();//method for all code to launch the game
	virtual void applicationDidEnterBackground();
	virtual void applicationWillEnterForeground();
};