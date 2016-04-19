#pragma once
#include "cocos2d.h"
#include "Export.h"
#include "TowerBase.h"
#include "GameStates.h"
#include "GameOverScene.h"
#include "Bike.h"
#include "HUD.h"
#include "GameData.h"
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
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	std::shared_ptr<GameData> m_ptr;
	Player * player;
	PowerUp * powerUp;
	bool speed;
	void StopSpeed(float dt);
	cocos2d::Sprite *cameraTarget;
	cocos2d::Sprite *backgroundSprite;
	cocos2d::Sprite *backgroundSprite2;
	cocos2d::Sprite *backgroundSprite3;
	cocos2d::Sprite *backgroundSprite4;
	cocos2d::Sprite *backgroundSprite5;
	cocos2d::Follow *camera;
	cocos2d::Label *label;
	cocos2d::Label *scoreLabel;
	cocos2d::MenuItemSprite *pauseItem;
	cocos2d::ProgressTimer *progressTimer;
	std::string const TOWERS_SPRITE_BATCH = "TowerBases";
	std::string const COINS_SPRITE_BATCH = "Coins";
	GameStates m_gameState;
	bool powerUpBool;
	std::vector<TowerBase *> m_towerBases;  // add this
	void createTowerBases();    // add this
	std::vector<Coin *> m_coins;  // add this
	void createCoins();    // add this
	std::vector<Police *> m_polices;  // add this
	void createPolice();    // add this
	std::vector<Ambulance *> m_ambulances;  // add this
	void createAmbulances();    // add this
	std::vector<Truck *> m_trucks;  // add this
	void createTrucks();    // add this
	std::vector<MiniTruck *> m_miniTrucks;  // add this
	void createMTrucks();    // add this
	std::vector<Bike *> m_bikes;  // add this
	void createBikes();    // add this
	void ScrollBackground(float dt);
	// Called when user pauses gameplay.
	void update(float dt);
	// Called at game over 
	void activateGameOverScene(float dt);
	void activatePauseScene(Ref *pSender);
	void addBackGroundSprite(cocos2d::Size const & visibleSize, cocos2d::Point const & origin);
	bool move;
	const char* achievementID = "CgkI69-MotMIEAIQAQ";
	bool onContactBegin(cocos2d::PhysicsContact &contact);
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event);
	void Crash();
	cocos2d::PhysicsWorld * sceneWorld;
	void SetPhysicsWorld(cocos2d::PhysicsWorld * world) { sceneWorld = world; };
	//void OnAcceleration(cocos2d::Acceleration * acc, cocos2d::Event * event);
	virtual void OnAcceleration(cocos2d::CCAcceleration* pAccelerationValue, cocos2d::Event * event);
	CREATE_FUNC(Tutorial);
};