#pragma once
#include "cocos2d.h"
#include "Export.h"
#include "HUD.h"
#include "TowerBase.h"
#include "GameStates.h"
#include "PauseScene.h"
#include "EndlessGameOver.h"
#include "GameData.h"
#include "Player.h"
#include "PowerUp.h"
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


class Endless : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	int randX1;
	int randX2;
	int yPos;
	int	xPos;
	int playerTemp1 = 3000;
	int playerTemp2 = 5000;
	int playerTemp3 = 7000;
	int backTemp1 = 6596;
	int backTemp2 = 8596;
	int backTemp3 = 10596;
	int tempRand1;
	int tempRand2;
	int preTemp;
	bool cont;
	int preTemp2;
	int count;
	int randCar;
	float temp;
	Player * player;
	HUD * hud;
	PowerUp * powerUp;
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
	void createTowerBases(int x, int y);    // add this
	std::vector<Coin *> m_coins;  // add this
	void createCoins();    // add this
	std::vector<Police *> m_polices;  // add this
	void createPolice(int x, int y);    // add this
	std::vector<Ambulance *> m_ambulances;  // add this
	void createAmbulances(int x, int y);    // add this
	std::vector<Truck *> m_trucks;  // add this
	void createTrucks(int x, int y);    // add this
	std::vector<MiniTruck *> m_miniTrucks;  // add this
	void createMTrucks(int x, int y);    // add this
	void ScrollBackground(float dt);
	// Called when user pauses gameplay.
	void activatePauseScene(Ref *pSender);
	void update(float dt);
	void createCars(int x, int y);    // add this
	std::vector<Police *> m_cars;  // add this
	void EndlessGame(float dt);
	void Timer(float dt);
	// Called at game over 
	void activateGameOverScene(float dt);
	void activateLoadingScene(float dt);
	void addBackGroundSprite(cocos2d::Size const & visibleSize, cocos2d::Point const & origin);
	bool move;
	unsigned int score;
	const char* achievementID = "CgkI69-MotMIEAIQAQ";
	bool onContactBegin(cocos2d::PhysicsContact &contact);
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event);
	void Crash();
	void Particles();
	cocos2d::PhysicsWorld * sceneWorld;
	void SetPhysicsWorld(cocos2d::PhysicsWorld * world) { sceneWorld = world; };
	//void OnAcceleration(cocos2d::Acceleration * acc, cocos2d::Event * event);
	virtual void OnAcceleration(cocos2d::CCAcceleration* pAccelerationValue, cocos2d::Event * event);
	CREATE_FUNC(Endless);
};