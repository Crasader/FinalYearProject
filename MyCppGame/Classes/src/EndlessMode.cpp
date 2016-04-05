#include "EndlessMode.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Endless::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = Endless::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());

	scene->addChild(layer);

	return scene;
}

void Endless::activatePauseScene(Ref *pSender)
{
	auto scene = PauseMenu::createScene();
	Director::getInstance()->pushScene(scene);
}

void Endless::activateLoadingScene(float dt)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/LevelCompleted.mp3");
	if (SonarCocosHelper::GooglePlayServices::isSignedIn)
	{
		SonarCocosHelper::GooglePlayServices::submitScore("CgkI69-MotMIEAIQAg", score);
	}
	auto scene = Loading::createScene();
	Director::getInstance()->replaceScene(scene);
}

void Endless::activateGameOverScene(float dt)
{
	auto scene = GameOver::createScene();
	Director::getInstance()->replaceScene(scene);
}

void Endless::addBackGroundSprite(cocos2d::Size const & visibleSize, cocos2d::Point const & origin)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();

	int i = cocos2d::RandomHelper::random_int(1, 4);
	if (i == 1)
	{
		backgroundSprite = Sprite::create
			(ptr->m_backgroundTextureFile);
		backgroundSprite->setPosition(Point((visibleSize.width / 2) +
			origin.x, (visibleSize.height) + 500));

		backgroundSprite2 = Sprite::create
			(ptr->m_backgroundTextureFile);
		backgroundSprite2->setPosition(Point((visibleSize.width / 2) +
			origin.x, (visibleSize.height) + 2596));

		backgroundSprite3 = Sprite::create
			(ptr->m_backgroundTextureFile);
		backgroundSprite3->setPosition(Point((visibleSize.width / 2) +
			origin.x, (visibleSize.height) + 4596));
	}

	if (i == 2)
	{
		backgroundSprite = Sprite::create
			(ptr->m_backgroundTextureFile1);
		backgroundSprite->setPosition(Point((visibleSize.width / 2) +
			origin.x, (visibleSize.height) + 500));

		backgroundSprite2 = Sprite::create
			(ptr->m_backgroundTextureFile1);
		backgroundSprite2->setPosition(Point((visibleSize.width / 2) +
			origin.x, (visibleSize.height) + 2596));

		backgroundSprite3 = Sprite::create
			(ptr->m_backgroundTextureFile1);
		backgroundSprite3->setPosition(Point((visibleSize.width / 2) +
			origin.x, (visibleSize.height) + 4596));
	}

	if (i == 3)
	{
		backgroundSprite = Sprite::create
			(ptr->m_backgroundTextureFile2);
		backgroundSprite->setPosition(Point((visibleSize.width / 2) +
			origin.x, (visibleSize.height) + 500));

		backgroundSprite2 = Sprite::create
			(ptr->m_backgroundTextureFile2);
		backgroundSprite2->setPosition(Point((visibleSize.width / 2) +
			origin.x, (visibleSize.height) + 2596));

		backgroundSprite3 = Sprite::create
			(ptr->m_backgroundTextureFile2);
		backgroundSprite3->setPosition(Point((visibleSize.width / 2) +
			origin.x, (visibleSize.height) + 4596));
	}

	if (i == 4)
	{
		backgroundSprite = Sprite::create
			(ptr->m_backgroundTextureFile3);
		backgroundSprite->setPosition(Point((visibleSize.width / 2) +
			origin.x, (visibleSize.height) + 500));

		backgroundSprite2 = Sprite::create
			(ptr->m_backgroundTextureFile3);
		backgroundSprite2->setPosition(Point((visibleSize.width / 2) +
			origin.x, (visibleSize.height) + 2596));

		backgroundSprite3 = Sprite::create
			(ptr->m_backgroundTextureFile3);
		backgroundSprite3->setPosition(Point((visibleSize.width / 2) +
			origin.x, (visibleSize.height) + 4596));
	}

	this->addChild(backgroundSprite, -1);
	this->addChild(backgroundSprite2, -1);
	this->addChild(backgroundSprite3, -1);
}

void Endless::ScrollBackground(float dt)
{
	//player->createBody(player);
	powerUpBool = false;
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/PowerUpOver.mp3");
}

bool Endless::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->scheduleOnce(schedule_selector(Endless::EndlessGame), 0.0f);
	yPos = 550;
	m_gameState = GameStates::PlaceGunTower;
	score = 0;
	move = true;
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/scoreSound.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/crashSound.mp3");

	tempRand1 = 7;
	tempRand2 = 8;

	pauseItem =
		MenuItemImage::create("GameScreen/Pause_Button.png",
			"GameScreen/Pause_Button(Click).png",
			CC_CALLBACK_1(Endless::activatePauseScene, this));

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	//auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 2);

	//auto edgeNode = Node::create();
	//edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//edgeNode->setPhysicsBody(edgeBody);

	//this->addChild(edgeNode);

	powerUpBool = false;

	//pauseItem->setPosition(Point(pauseItem->getContentSize().width -
	//	(pauseItem->getContentSize().width / 4) + origin.x,
	//	visibleSize.height - pauseItem->getContentSize().height +
	//	(pauseItem->getContentSize().width / 4) + origin.y));

	pauseItem->setPosition(22, 520);

	player = Player::create();
	player->setPosition(100, 125);
	player->setAnchorPoint(Point(0.5f, 0.55f));
	this->addChild(player, 5);

	powerUp = PowerUp::create();
	powerUp->setPosition(195, 1500);
	this->addChild(powerUp);

	hud = HUD::create();
	hud->setPosition(340, 530);
	this->addChild(hud, 6);

	label = Label::createWithTTF("Score:", "fonts/Marker Felt.ttf", 32);
	label->setPosition(320, 522);
	this->addChild(label, 7);
	__String *tempScore = __String::createWithFormat("%i", score);
	scoreLabel = Label::createWithTTF(tempScore->getCString(), "fonts/Marker Felt.ttf", 32);
	scoreLabel->setPosition(377, 522);
	this->addChild(scoreLabel, 7);

	auto menu = Menu::create(pauseItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	addBackGroundSprite(visibleSize, origin);
	/*createTowerBases();
	createCoins();
	createPolice();
	createAmbulances();
	createMTrucks();
	createTrucks();*/

	/*auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(Endless::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Endless::onTouchMoved, this);*/
	for (int i = 0; i < 100; i++)
	{
		EndlessGame(temp);
	}

	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	auto screenSize = glview->getFrameSize();
	if (player->getPositionX() > 500)
	{
		//float temp = screenSize.width - 10;
		player->setPositionX(499);
	}
	if (player->getPositionX() < 0)
	{
		player->setPositionX(1);
	}

	Device::setAccelerometerEnabled(true);
	auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(Endless::OnAcceleration, this));


	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Endless::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	cameraTarget = Sprite::create();
	cameraTarget->setPositionX(visibleSize.width / 2);
	cameraTarget->setPositionY(player->getPosition().y - 115);
	this->scheduleUpdate();
	//this->schedule(schedule_selector(Endless::EndlessGame), 0.25f);
	this->schedule(schedule_selector(Endless::Timer), 1.0f);
	this->addChild(cameraTarget);
	camera = Follow::create(cameraTarget, Rect::ZERO);
	camera->retain();
	this->runAction(camera);
	return true;
}

void Endless::update(float dt)
{
	if (move == true)
	{
		scoreLabel->setPositionY(scoreLabel->getPosition().y + 7.5);
		label->setPositionY(label->getPosition().y + 7.5);
		hud->setPositionY(hud->getPosition().y + 7.5);
		pauseItem->setPositionY(pauseItem->getPosition().y + 7.5);
		player->setPositionY(player->getPosition().y + 7.5);
	}
	//if (player->getPosition().y > playerTemp1)
	//{
	//	Size visibleSize = Director::getInstance()->getVisibleSize();
	//	Point origin = Director::getInstance()->getVisibleOrigin();
	//	backgroundSprite->setPosition(Point((visibleSize.width / 2) +
	//		origin.x, (visibleSize.height) + backTemp1));
	//}

	//if (player->getPosition().y > playerTemp2)
	//{
	//	Size visibleSize = Director::getInstance()->getVisibleSize();
	//	Point origin = Director::getInstance()->getVisibleOrigin();
	//	backgroundSprite2->setPosition(Point((visibleSize.width / 2) +
	//		origin.x, (visibleSize.height) + backTemp2));
	//	backTemp1 += 2000;
	//}

	//if (player->getPosition().y > playerTemp3)
	//{
	//	Size visibleSize = Director::getInstance()->getVisibleSize();
	//	Point origin = Director::getInstance()->getVisibleOrigin();
	//	backgroundSprite3->setPosition(Point((visibleSize.width / 2) +
	//		origin.x, (visibleSize.height) + backTemp3));
	//	backTemp2 += 2000;
	//}
	if (player->getPosition().x < 25)
	{
		player->setPositionX(26);
	}
	if (player->getPosition().x > 372)
	{
		player->setPositionX(371);
	}
	cameraTarget->setPositionY(player->getPosition().y + 115);
	//EndlessGame(temp);
	//Particles();
}

void Endless::Timer(float dt)
{
	if (move == true)
	{
		score = score + 1;
		__String *tempScore = __String::createWithFormat("%i", score);
		scoreLabel->setString(tempScore->getCString());
	}
}

void Endless::EndlessGame(float dt)
{
		randX1 = cocos2d::RandomHelper::random_int(1, 3);
		if ((randX1 == tempRand1 || randX1 == tempRand2)&&(count == 1))
		{
			if (randX1 == 1)
			{
				randX1 = cocos2d::RandomHelper::random_int(2, 3);
				if (randX1 == 2)
				{
					xPos = 195;
				}
				if (randX1 == 3)
				{
					xPos = 340;
				}
			}
			if (randX1 == 2)
			{
				randX1 = cocos2d::RandomHelper::random_int(7, 8);
				if (randX1 == 7)
				{
					xPos = 60;
				}
				if (randX1 == 8)
				{
					xPos = 340;
				}
			}
			if (randX1 == 3)
			{
				randX1 = cocos2d::RandomHelper::random_int(1, 2);
				if (randX1 == 1)
				{
					xPos = 60;
				}
				if (randX1 == 2)
				{
					xPos = 195;
				}
			}
			cont = true;
			preTemp2 = randX1;
		}
		tempRand1 = randX1;
		preTemp = randX1;
		if (randX1 == 1)
		{
			xPos = 60;
		}
		if (randX1 == 2)
		{
			xPos = 195;
		}
		if (randX1 == 3)
		{
			xPos = 340;
		}
		
		randCar = cocos2d::RandomHelper::random_int(1, 5);
		if (randCar == 1)
		{
			createTrucks(xPos, yPos);
		}
		else if (randCar == 2)
		{
			createTowerBases(xPos, yPos);
		}
		else if (randCar == 3)
		{
			createPolice(xPos, yPos);
		}
		else if (randCar == 4)
		{
			createAmbulances(xPos, yPos);
		}
		else if (randCar == 5)
		{
			createMTrucks(xPos, yPos);
		}

		randX2 = cocos2d::RandomHelper::random_int(1, 3);

		if (randX2 == tempRand1)
		{
			if (tempRand1 == 1)
			{
				randX2 = cocos2d::RandomHelper::random_int(2, 3);
				if (randX2 == 2)
				{
					xPos = 195;
				}
				if (randX2 == 3)
				{
					xPos = 340;
				}
			}
			if (tempRand1 == 2)
			{
				randX2 = cocos2d::RandomHelper::random_int(7, 8);
				if (randX2 == 7)
				{
					xPos = 60;
				}
				if (randX2 == 8)
				{
					xPos = 340;
				}
			}
			if (tempRand1 == 3)
			{
				randX2 = cocos2d::RandomHelper::random_int(1, 2);
				if (randX2 == 1)
				{
					xPos = 60;
				}
				if (randX2 == 2)
				{
					xPos = 195;
				}
			}

			tempRand2 = randX2;
			randCar = cocos2d::RandomHelper::random_int(1, 5);
			if (randCar == 1)
			{
				createTrucks(xPos, yPos);
			}
			else if (randCar == 2)
			{
				createTowerBases(xPos, yPos);
			}
			else if (randCar == 3)
			{
				createPolice(xPos, yPos);
			}
			else if (randCar == 4)
			{
				createAmbulances(xPos, yPos);
			}
			else if (randCar == 5)
			{
				createMTrucks(xPos, yPos);
			}
		}
		else if (cont == true)
		{
			if (preTemp2 == 1)
			{
				randX1 = cocos2d::RandomHelper::random_int(2, 3);
				if (randX1 == 2)
				{
					xPos = 195;
				}
				if (randX1 == 3)
				{
					xPos = 340;
				}
			}
			if (preTemp2 == 2)
			{
				randX1 = cocos2d::RandomHelper::random_int(7, 8);
				if (randX1 == 7)
				{
					xPos = 60;
				}
				if (randX1 == 8)
				{
					xPos = 340;
				}
			}
			if (preTemp2 == 3)
			{
				randX1 = cocos2d::RandomHelper::random_int(1, 2);
				if (randX1 == 1)
				{
					xPos = 60;
				}
				if (randX1 == 2)
				{
					xPos = 195;
				}
			}
			cont = false;
		}
		else
		{
			if (randX2 == 1)
			{
				xPos = 60;
			}
			if (randX2 == 2)
			{
				xPos = 195;
			}
			if (randX2 == 3)
			{
				xPos = 340;
			}
			tempRand2 = randX2;
			randCar = cocos2d::RandomHelper::random_int(1, 5);
			if (randCar == 1)
			{
				createTrucks(xPos, yPos);
			}
			else if (randCar == 2)
			{
				createTowerBases(xPos, yPos);
			}
			else if (randCar == 3)
			{
				createPolice(xPos, yPos);
			}
			else if (randCar == 4)
			{
				createAmbulances(xPos, yPos);
			}
			else if (randCar == 5)
			{
				createMTrucks(xPos, yPos);
			}
		}

		if (tempRand1 == randX1 && tempRand2 == randX2 || tempRand2 == randX1 && tempRand1 == randX2)
		{
			count = count + 1;
		}
		else
		{
			count = 0;
		}
		yPos = yPos + 500;
}

bool Endless::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event)
{
	CCLOG("onTouchBegan x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);
	return true;
}

void Endless::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event)
{
	if (move == true)
	{
		player->setPosition(touch->getLocation().x, player->getPosition().y);
	}
}

void Endless::Particles()
{
	auto size = Director::getInstance()->getWinSize();
	auto m_emitter = ParticleSmoke::createWithTotalParticles(900);
	//m_emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("smoke.png"));
	m_emitter->setDuration(0.015f);
	m_emitter->setGravity(Point(0, -240));
	m_emitter->setAngle(0);
	m_emitter->setAngleVar(360);
	m_emitter->setRadialAccel(50);
	m_emitter->setRadialAccelVar(0);
	m_emitter->setTangentialAccel(0);
	m_emitter->setTangentialAccelVar(0);
	m_emitter->setPosVar(Point(1, 0));
	m_emitter->setLife(0.15f);
	m_emitter->setLifeVar(0.15f);
	m_emitter->setStartSpin(0);
	m_emitter->setStartSpinVar(0);
	m_emitter->setEndSpin(0);
	m_emitter->setEndSpinVar(0);
	m_emitter->setStartColor(Color4F(0, 0, 0, 1));
	m_emitter->setStartColorVar(Color4F(0, 0, 0, 0));
	m_emitter->setEndColor(Color4F(0, 0, 0, 1));
	m_emitter->setEndColorVar(Color4F(0, 0, 0, 0));
	m_emitter->setStartSize(7.5f);
	m_emitter->setStartSizeVar(0);
	m_emitter->setEndSize(2.0f);
	m_emitter->setEndSizeVar(0);
	m_emitter->setEmissionRate(80);
	m_emitter->setPosition(Vec2(player->getPosition().x + 15, player->getPosition().y - 72));
	addChild(m_emitter, 10);
}

void Endless::Crash()
{
	auto size = Director::getInstance()->getWinSize();
	auto m_emitter = ParticleExplosion::createWithTotalParticles(900);
	//m_emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("smoke.png"));

	m_emitter->setDuration(-1);
	m_emitter->setGravity(Point(0, -240));
	m_emitter->setAngle(0);
	m_emitter->setAngleVar(180);
	m_emitter->setRadialAccel(25);
	m_emitter->setRadialAccelVar(0);
	m_emitter->setTangentialAccel(10);
	m_emitter->setTangentialAccelVar(0);
	m_emitter->setPosVar(Point(1, 0));
	m_emitter->setLife(0.25);
	m_emitter->setLifeVar(0.50);
	m_emitter->setStartSpin(0);
	m_emitter->setStartSpinVar(0);
	m_emitter->setEndSpin(0);
	m_emitter->setEndSpinVar(0);
	m_emitter->setStartColor(Color4F(212, 73, 0, 1));
	m_emitter->setStartColorVar(Color4F(0, 0, 0, 0));
	m_emitter->setEndColor(Color4F(212, 73, 0, 1));
	m_emitter->setEndColorVar(Color4F(0, 0, 0, 0));
	m_emitter->setStartSize(20.0f);
	m_emitter->setStartSizeVar(0);
	m_emitter->setEndSize(15.0f);
	m_emitter->setEndSizeVar(0);
	m_emitter->setEmissionRate(275);
	m_emitter->setPosition(Vec2(player->getPosition().x, player->getPosition().y - 15));
	addChild(m_emitter, 10);
}

void Endless::OnAcceleration(cocos2d::CCAcceleration* pAcceleration, cocos2d::Event * event)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	float xA = player->getPosition().x;
	float yA = player->getPosition().y;

	float w = visibleSize.width;

	xA = xA + (pAcceleration->x * w * 0.05);
	if (move == true)
	{
		player->setPosition(xA, yA);
	}
}


void Endless::createTowerBases(int x, int y)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_textureAtlasImageFile);
		TowerBase * base = TowerBase::create(Vec2(x, y), m_gameState);
		m_towerBases.push_back(base);
		spritebatch->addChild(base, 1);
	this->addChild(spritebatch, 1, TOWERS_SPRITE_BATCH);
}

void Endless::createCoins()
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_textureAtlasImageFile);

	for (int i = 0; i < ptr->m_numberOfCoins; i++)
	{
		Coin * base = Coin::create(Vec2(ptr->m_coinPosX[i], ptr->m_coinPosY[i]), m_gameState);
		m_coins.push_back(base);
		spritebatch->addChild(base, 1);
	}
	this->addChild(spritebatch, 4, COINS_SPRITE_BATCH);
}

void Endless::createPolice(int x, int y)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_textureAtlasImageFile);
		Police * base = Police::create(Vec2(x,y), m_gameState);
		m_polices.push_back(base);
		spritebatch->addChild(base, 1);
	this->addChild(spritebatch, 1, COINS_SPRITE_BATCH);
}

void Endless::createAmbulances(int x, int y)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_textureAtlasImageFile);

		Ambulance * base = Ambulance::create(Vec2(x,y), m_gameState);
		m_ambulances.push_back(base);
		spritebatch->addChild(base, 1);
	this->addChild(spritebatch, 1, COINS_SPRITE_BATCH);
}

void Endless::createMTrucks(int x, int y)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_textureAtlasImageFile);
		MiniTruck * base = MiniTruck::create(Vec2(x,y), m_gameState);
		m_miniTrucks.push_back(base);
		spritebatch->addChild(base, 1);
	this->addChild(spritebatch, 1, COINS_SPRITE_BATCH);
}

void Endless::createTrucks(int x, int y)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_textureAtlasImageFile);
		Truck * base = Truck::create(Vec2(x,y), m_gameState);
		m_trucks.push_back(base);
		spritebatch->addChild(base, 1);
	this->addChild(spritebatch, 1, COINS_SPRITE_BATCH);
}

bool Endless::onContactBegin(cocos2d::PhysicsContact &contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA && nodeB)
	{
		if (nodeA->getTag() == 10)
		{
			if (nodeB->getTag() == 30)
			{
				score = score + 10;
				__String *tempScore = __String::createWithFormat("%i", score);
				scoreLabel->setString(tempScore->getCString());
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/scoreSound.mp3");
				nodeB->removeFromParentAndCleanup(true);
				if (SonarCocosHelper::GooglePlayServices::isSignedIn)
				{
					SonarCocosHelper::GooglePlayServices::incrementAchievement("CgkI69-MotMIEAIQAA", 1);
				}
			}

			else if (nodeB->getTag() == 40)
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/PowerUpCollected.mp3");
				score = score + 1000;
				__String *tempScore = __String::createWithFormat("%i", score);
				scoreLabel->setString(tempScore->getCString());
				nodeB->removeFromParentAndCleanup(true);
				powerUpBool = true;
				this->scheduleOnce(schedule_selector(Endless::ScrollBackground), 5.0f);
			}
		}
		else if (nodeA->getTag() == 30)
		{
			score = score + 10;
			__String *tempScore = __String::createWithFormat("%i", score);
			scoreLabel->setString(tempScore->getCString());
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/scoreSound.mp3");
			nodeA->removeFromParentAndCleanup(true);
			if (SonarCocosHelper::GooglePlayServices::isSignedIn)
			{
				SonarCocosHelper::GooglePlayServices::incrementAchievement("CgkI69-MotMIEAIQAA", 1);
			}
		}
		else if (nodeA->getTag() == 40)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/PowerUpCollected.mp3");
			score = score + 1000;
			__String *tempScore = __String::createWithFormat("%i", score);
			scoreLabel->setString(tempScore->getCString());
			nodeA->removeFromParentAndCleanup(true);
			powerUpBool = true;
			this->scheduleOnce(schedule_selector(Endless::ScrollBackground), 3.0f);
		}
	}

	if ((0x000001 == a->getCollisionBitmask() && 0x000002 == b->getCollisionBitmask() || 0x000001 == b->getCollisionBitmask() && 0x000002 == a->getCollisionBitmask()))
	{
		if (powerUpBool == false)
		{
			this->scheduleOnce(schedule_selector(Endless::activateGameOverScene), 3.0f);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/crashSound.mp3");
			move = false;
			Crash();
			if (SonarCocosHelper::GooglePlayServices::isSignedIn)
			{
				SonarCocosHelper::GooglePlayServices::unlockAchievement(achievementID);
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/GameOver.mp3");
		}
	}
	return true;
}