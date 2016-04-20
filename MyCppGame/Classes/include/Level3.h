#pragma once
#include "cocos2d.h"
#include "Export.h"
#include "HUD.h"
#include "TowerBase.h"
#include "GameStates.h"
#include "PauseScene.h"
#include "GameOverScene.h"
#include "GameCompleteScene.h"
#include "GameData.h"
#include "Player.h"
#include "Bike.h"
#include "PowerUp.h"
#include "LevelLoader.h"
#include "Coin.h"
#include "Police.h"
#include "Truck.h"
#include "MiniTruck.h"
#include "Ambulance.h"
#include "LoadingScene.h"
#include "2d/CCParticleSystemQuad.h"
#include <algorithm>
#include <vector>
#include <string>
#include "SonarFrameworks.h"


class Level3 : public cocos2d::Layer
{
private:
	Player * player;
	HUD * hud;
	PowerUp * powerUp;
	std::string level;
	bool speed;
	cocos2d::Sprite *cameraTarget;//camera sprite
	cocos2d::Sprite *backgroundSprite;//background sprite
	cocos2d::Sprite *backgroundSprite2;//background sprite
	cocos2d::Sprite *backgroundSprite3;//background sprite
	cocos2d::Sprite *backgroundSprite4;//background sprite
	cocos2d::Sprite *backgroundSprite5;//background sprite
	cocos2d::Follow *camera;
	cocos2d::Label *label;
	cocos2d::Label *scoreLabel;
	cocos2d::MenuItemSprite *pauseItem;//menu sprite used to create pause button
	cocos2d::ProgressTimer *progressTimer;
	std::string const TOWERS_SPRITE_BATCH = "TowerBases";
	std::string const COINS_SPRITE_BATCH = "Coins";
	bool powerUpBool;//bool to check to see if power up 1 is active or not
	std::vector<TowerBase *> m_towerBases;  //array for storing taxis
	std::vector<Coin *> m_coins;  //array for storing coins
	std::vector<Police *> m_polices;   //array for storing police cars
	std::vector<Ambulance *> m_ambulances;  //array for storing ambulances
	std::vector<Truck *> m_trucks;  //array for storing trucks
	std::vector<MiniTruck *> m_miniTrucks;  //array for storing mini trucks
	std::vector<Bike *> m_bikes;  //array for storing bikes
	bool move;//bool to check if car is moving or not
	unsigned int score;// score variable
	const char* achievementID = "CgkI69-MotMIEAIQAQ";// id used for google play trophy
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	std::shared_ptr<GameData> m_ptr;
	void StopSpeed(float dt);//method to stop the speed boost 
	GameStates m_gameState;
	void createTowerBases();    //method to create the taxis
	void createCoins();    //method used to create coins
	void createPolice();    //method used to create police cars
	void createAmbulances();    //method used to create ambulances 
	void createTrucks();     //method used to create trucks
	void createMTrucks();    //method used to create mini trucks
	void createBikes();    //method used to create bikes
	void DeactivatePowerUp(float dt);// method for deactivating power up ability
	void activatePauseScene(Ref *pSender);// Called when user pauses gameplay.
	void update(float dt);
	void activateGameOverScene(float dt);// Called at game over 
	void activateLoadingScene(float dt);//changes to the loading next level scene
	void addBackGroundSprite(cocos2d::Size const & visibleSize, cocos2d::Point const & origin);//add the backgrounds to the scene
	bool onContactBegin(cocos2d::PhysicsContact &contact);//method that checks for collision between physics bodies
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event);
	void Crash();//method that draws the particles to the scene for a crash fire effect
	void Particles(); //method that adds particles for a gas effect coiming from the back of the car
	cocos2d::PhysicsWorld * sceneWorld;
	void SetPhysicsWorld(cocos2d::PhysicsWorld * world) { sceneWorld = world; };//sets the world up as a physics world
	virtual void OnAcceleration(cocos2d::CCAcceleration* pAccelerationValue, cocos2d::Event * event);//metjo that checks or movement on the device so it will move the car in that direction
	CREATE_FUNC(Level3);
};