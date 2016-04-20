#pragma once
#include "cocos2d.h"
#include "Export.h"
#include "TowerBase.h"
#include "GameStates.h"
#include "GameOverScene.h"
#include "TutorialOverScene.h"
#include "TutorialPauseScene.h"
#include "Bike.h"
#include "HUD.h"
#include "GameData.h"
#include "TutorialInfo1.h"
#include "TutorialInfo2.h"
#include "TutorialInfo3.h"
#include "TutorialInfo4.h"
#include "Player.h"
#include "PowerUp.h"
#include "LevelLoader.h"
#include "Coin.h"
#include "Police.h"
#include "PauseScene.h"
#include "Truck.h"
#include "MiniTruck.h"
#include "Ambulance.h"
#include <algorithm>
#include <vector>
#include <string>
#include "SonarFrameworks.h"


class Tutorial : public cocos2d::Layer
{
private:
	Player * player;
	PowerUp * powerUp;
	bool speed;
	cocos2d::Sprite *cameraTarget;//camera sprite
	cocos2d::Sprite *backgroundSprite;//background sprite
	cocos2d::Sprite *backgroundSprite2;//background sprite
	cocos2d::Sprite *backgroundSprite3;//background sprite
	cocos2d::Sprite *backgroundSprite4;//background sprite
	cocos2d::Sprite *backgroundSprite5;//background sprite
	cocos2d::Follow *camera;//follow camera
	cocos2d::Label *label;
	cocos2d::Label *scoreLabel;
	cocos2d::MenuItemSprite *pauseItem;//menu item for the pause button
	cocos2d::ProgressTimer *progressTimer;
	std::string const TOWERS_SPRITE_BATCH = "TowerBases";
	std::string const COINS_SPRITE_BATCH = "Coins";
	bool powerUpBool;//bool to check to see if power up 1 is active
	std::vector<TowerBase *> m_towerBases;  //array for taxi cars
	std::vector<Coin *> m_coins;  //array for coins
	std::vector<Police *> m_polices;  //array for police cars
	std::vector<Ambulance *> m_ambulances;  //array for ambulances
	std::vector<Truck *> m_trucks;  //array for trucks
	std::vector<MiniTruck *> m_miniTrucks;  //array for mini trucks
	std::vector<Bike *> m_bikes;  //array for bikes
	bool move;//bool to check if car is moving or not
	const char* achievementID = "CgkI69-MotMIEAIQAQ";// id used for google play trophy
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	std::shared_ptr<GameData> m_ptr;
	void StopSpeed(float dt);//method to stop the speed boost 
	GameStates m_gameState;
	void createTowerBases();    //method to create the taxis
	void createCoins();   //method to create the coins
	void createPolice();    //method to create the police cars
	void createAmbulances();   //method to create the abulances
	void createTrucks();   //method to create the trucks
	void createMTrucks();    //method to create the mini trucks
	void createBikes();    //method to create the bikes
	void DeactivatePowerUp(float dt);//deactivates the power up 1
	void update(float dt);
	void activateGameOverScene(float dt);// Called at game over 
	void activatePauseScene(Ref *pSender);// Called when user pauses gameplay.
	void activateTutorialInfo1(Ref *pSender);// changes scene to info 1 on tutorial slides
	void activateTutorialInfo2(Ref *pSender);// changes scene to info 2 on tutorial slides
	void activateTutorialInfo3(Ref *pSender);// changes scene to info 3 on tutorial slides
	void activateTutorialInfo4(Ref *pSender);// changes scene to info 4 on tutorial slides
	void addBackGroundSprite(cocos2d::Size const & visibleSize, cocos2d::Point const & origin);//add the backgrounds to the scene
	bool onContactBegin(cocos2d::PhysicsContact &contact);//method that checks for collision between physics bodies
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event);
	void Crash();//method that creates the fire particles for crashes
	cocos2d::PhysicsWorld * sceneWorld;
	void SetPhysicsWorld(cocos2d::PhysicsWorld * world) { sceneWorld = world; };//sets the world up as a physics world
	virtual void OnAcceleration(cocos2d::CCAcceleration* pAccelerationValue, cocos2d::Event * event);//metjo that checks or movement on the device so it will move the car in that direction
	CREATE_FUNC(Tutorial);
};