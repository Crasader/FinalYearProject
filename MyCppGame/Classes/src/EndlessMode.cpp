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
	auto scene = PauseLevel2::createScene();
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
	auto scene = EndlessGameOver::createScene();
	Director::getInstance()->replaceScene(scene);
}

void Endless::addBackGroundSprite(cocos2d::Size const & visibleSize, cocos2d::Point const & origin)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();

		backgroundSprite = Sprite::create
			(ptr->m_backgroundTextureFile6);
		backgroundSprite->setPosition(Point((visibleSize.width / 2) +
			origin.x, (visibleSize.height) + 500));

		backgroundSprite2 = Sprite::create
			(ptr->m_backgroundTextureFile6);
		backgroundSprite2->setPosition(Point((visibleSize.width / 2) +
			origin.x, (visibleSize.height) + 2596));

		backgroundSprite3 = Sprite::create
			(ptr->m_backgroundTextureFile6);
		backgroundSprite3->setPosition(Point((visibleSize.width / 2) +
			origin.x, (visibleSize.height) + 4596));

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

void Endless::StopSpeed(float dt)
{
	speed = false;
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
	coinY = 800;
	powerY = 4400;
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

	powerUpBool = false;

	pauseItem->setPosition(22, 520);

	player = Player::create();
	player->setPosition(195, 125);
	player->setAnchorPoint(Point(0.5f, 0.55f));
	this->addChild(player, 5);

	hud = HUD::create();
	hud->setPosition(333, 530);
	this->addChild(hud, 6);

	label = Label::createWithTTF("Score:", "fonts/Marker Felt.ttf", 32);
	label->setPosition(312, 522);
	this->addChild(label, 7);
	__String *tempScore = __String::createWithFormat("%i", score);
	scoreLabel = Label::createWithTTF(tempScore->getCString(), "fonts/Marker Felt.ttf", 32);
	scoreLabel->setPosition(369, 522);
	this->addChild(scoreLabel, 7);

	auto menu = Menu::create(pauseItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	addBackGroundSprite(visibleSize, origin);

	for (int i = 0; i < 100; i++)
	{
		EndlessGame(temp);
	}

	for (int i = 0; i < 50; i++)
	{
		RandomCoins(temp);
	}

	for (int i = 0; i < 4; i++)
	{
		RandomPowerUps(temp);
	}

	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	auto screenSize = glview->getFrameSize();
	if (player->getPositionX() > 500)
	{
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
	this->schedule(schedule_selector(Endless::UpdateScore), 1.0f);
	//this->schedule(schedule_selector(Endless::moveBack), 0.1f);
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
		scoreLabel->setPositionY(scoreLabel->getPosition().y + 8.5);
		label->setPositionY(label->getPosition().y + 8.5);
		hud->setPositionY(hud->getPosition().y + 8.5);
		pauseItem->setPositionY(pauseItem->getPosition().y + 8.5);
		player->setPositionY(player->getPosition().y + 8.5);
		backgroundSprite->setPositionY(backgroundSprite->getPosition().y + 8.5);
		backgroundSprite2->setPositionY(backgroundSprite->getPosition().y + 8.5);
		backgroundSprite3->setPositionY(backgroundSprite->getPosition().y + 8.5);
	}
	if (player->getPosition().x < 25)
	{
		player->setPositionX(26);
	}
	if (player->getPosition().x > 372)
	{
		player->setPositionX(371);
	}
	if (speed == true && move == true)
	{
		scoreLabel->setPositionY(scoreLabel->getPosition().y + 1.8);
		label->setPositionY(label->getPosition().y + 1.8);
		hud->setPositionY(hud->getPosition().y + 1.8);
		pauseItem->setPositionY(pauseItem->getPosition().y + 1.8);
		player->setPositionY(player->getPosition().y + 1.8);
		backgroundSprite->setPositionY(backgroundSprite->getPosition().y + 1.8);
		backgroundSprite2->setPositionY(backgroundSprite->getPosition().y + 1.8);
		backgroundSprite3->setPositionY(backgroundSprite->getPosition().y + 1.8);
	}
	cameraTarget->setPositionY(player->getPosition().y + 115);
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

void Endless::UpdateScore(float dt)
{
	if (speed == true)
	{
		score = score + 1;
		__String *tempScore = __String::createWithFormat("%i", score);
		scoreLabel->setString(tempScore->getCString());
	}
}

void Endless::EndlessGame(float dt)
{
	randX1 = cocos2d::RandomHelper::random_int(1, 3);
	//generates a random number to determine what lane the car will be placed in 
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
	tempRand1 = randX1;
	preTemp = randX1;

		
	randCar = cocos2d::RandomHelper::random_int(1, 5);
	//generates a random car type
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

	if (randX2 == tempRand1)//checks to make sure the second car isn't drawing in the same lane as the first car
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
		//generates a random car type
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
	else
	{
		//generates a random number to determine what lane the car will be placed in 
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
		//generates a random car type
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
	yPos = yPos + 500;//moves up the ypos so theres a gap between the rows of cars
}

void Endless::RandomCoins(float dt)
{
	randCoinX = cocos2d::RandomHelper::random_int(1, 3);
	//places the coin on a certain lanes depeneding on the random number
	if (randCoinX == 1)
	{
		coinX = 60;
	}
	if (randCoinX == 2)
	{
		coinX = 195;
	}
	if (randCoinX == 3)
	{
		coinX = 340;
	}
	createCoins(coinX, coinY);
	coinY += 1000;//moves the ypos up two rows of traffic for when drawing the next coin
}

void Endless::RandomPowerUps(float dt)
{
	randPowerX = cocos2d::RandomHelper::random_int(1, 3);
	//places the power on a certain lanes depeneding on the random number
	if (randPowerX == 1)
	{
		powerX = 60;
	}
	if (randPowerX == 2)
	{
		powerX = 195;
	}
	if (randPowerX == 3)
	{
		powerX = 340;
	}
	
	int randPower = cocos2d::RandomHelper::random_int(1, 3);//randomly generates what power up its going to be
	auto powerUp1 = PowerUp::create(randPower);
	powerUp1->setPosition(powerX, powerY);//sets the position to draw the power up
	this->addChild(powerUp1);
	powerY += 5000;//moves the ypos up a number rows of traffic for when drawing the next power up
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

void Endless::Particles()//particles that are use for emissions from the car
{

}

void Endless::Crash()// draws the animation for a crash and pasticles that fly out from there
{
	//animation code
	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile("GameScreen/explosion.plist");
	cocos2d::SpriteFrame* spriteFrame = spritecache->getSpriteFrameByName("explosion0.png");
	cocos2d::Vector<cocos2d::Sprite *> m_aiSprites;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames;
	for (int i = 0; i < 23; i++)
	{
		// Get a SpriteFrame using a name from the spritesheet .plist file.
		m_animFrames.pushBack(spritecache->getSpriteFrameByName("explosion" + std::to_string(i) + ".png"));
	}
	// Create the animation out of the frames.
	Animation* animation = Animation::createWithSpriteFrames(m_animFrames, 0.065);
	Animate* animate = Animate::create(animation);
	// Create a sprite using any one of the SpriteFrames
	// This is so we get a sprite of the correct dimensions.
	auto sprite = Sprite::createWithSpriteFrame(m_animFrames.at(0));
	// Run and repeat the animation.
	sprite->setScale(3.0f);
	sprite->runAction(RepeatForever::create(animate));
	sprite->setPosition(Vec2(player->getPosition().x, player->getPosition().y - 5));
	this->addChild(sprite, 10);
	m_aiSprites.pushBack(sprite);

	
	//code for the particles that will be coloured orange
	auto size = Director::getInstance()->getWinSize();
	auto m_emitter = ParticleExplosion::createWithTotalParticles(900);
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

	//sets xA and yA to the players position
	float xA = player->getPosition().x;
	float yA = player->getPosition().y;

	float w = visibleSize.width;

	xA = xA + (pAcceleration->x * w * 0.05);// checks to see how much the device has been tilted
	if (move == true)
	{
		player->setPosition(xA, yA);
	}
}


void Endless::createTowerBases(int x, int y)//creates the taxis
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_textureAtlasImageFile);
		TowerBase * base = TowerBase::create(Vec2(x, y), m_gameState);
		m_towerBases.push_back(base);
		spritebatch->addChild(base, 1);
	this->addChild(spritebatch, 1, TOWERS_SPRITE_BATCH);
}

void Endless::createCoins(int x, int y)//creates the coins
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_textureAtlasImageFile);
	Coin * base = Coin::create(Vec2(x,y), m_gameState);
	m_coins.push_back(base);
	spritebatch->addChild(base, 1);
	this->addChild(spritebatch, 4, COINS_SPRITE_BATCH);
}

void Endless::createPolice(int x, int y)//creates the police cars
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_textureAtlasImageFile);
		Police * base = Police::create(Vec2(x,y), m_gameState);
		m_polices.push_back(base);
		spritebatch->addChild(base, 1);
	this->addChild(spritebatch, 1, COINS_SPRITE_BATCH);
}

void Endless::createAmbulances(int x, int y)//creates the ambulances
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_textureAtlasImageFile);

		Ambulance * base = Ambulance::create(Vec2(x,y), m_gameState);
		m_ambulances.push_back(base);
		spritebatch->addChild(base, 1);
	this->addChild(spritebatch, 1, COINS_SPRITE_BATCH);
}

void Endless::createMTrucks(int x, int y)//creates the mini trucks
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_textureAtlasImageFile);
		MiniTruck * base = MiniTruck::create(Vec2(x,y), m_gameState);
		m_miniTrucks.push_back(base);
		spritebatch->addChild(base, 1);
	this->addChild(spritebatch, 1, COINS_SPRITE_BATCH);
}

void Endless::createTrucks(int x, int y)//creates the trucks
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
				score = score + 1;
				__String *tempScore = __String::createWithFormat("%i", score);
				scoreLabel->setString(tempScore->getCString());
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/scoreSound.mp3");
				nodeB->removeFromParentAndCleanup(true);
				if (SonarCocosHelper::GooglePlayServices::isSignedIn)
				{
					SonarCocosHelper::GooglePlayServices::unlockAchievement("CgkI69-MotMIEAIQDw");
					SonarCocosHelper::GooglePlayServices::incrementAchievement("CgkI69-MotMIEAIQCg", 1);
					SonarCocosHelper::GooglePlayServices::incrementAchievement("CgkI69-MotMIEAIQCQ", 1);
				}
			}

			else if (nodeB->getTag() == 40)
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/PowerUpCollected.mp3");
				nodeB->removeFromParentAndCleanup(true);
				powerUpBool = true;
				if (SonarCocosHelper::GooglePlayServices::isSignedIn)
				{
					SonarCocosHelper::GooglePlayServices::unlockAchievement("CgkI69-MotMIEAIQEA");
					SonarCocosHelper::GooglePlayServices::incrementAchievement("CgkI69-MotMIEAIQCA", 1);
				}
				this->scheduleOnce(schedule_selector(Endless::ScrollBackground), 5.0f);
			}

			else if (nodeB->getTag() == 50)
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/speedboost.mp3");
				nodeB->removeFromParentAndCleanup(true);
				speed -= true;
				if (SonarCocosHelper::GooglePlayServices::isSignedIn)
				{
					SonarCocosHelper::GooglePlayServices::unlockAchievement("CgkI69-MotMIEAIQEA");
					SonarCocosHelper::GooglePlayServices::incrementAchievement("CgkI69-MotMIEAIQCA", 1);
				}
				this->scheduleOnce(schedule_selector(Endless::StopSpeed), 4.5f);
			}
			else if (nodeB->getTag() == 60)
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/ScoreBoost.mp3");
				score = score + 2;
				__String *tempScore = __String::createWithFormat("%i", score);
				scoreLabel->setString(tempScore->getCString());
				if (SonarCocosHelper::GooglePlayServices::isSignedIn)
				{
					SonarCocosHelper::GooglePlayServices::unlockAchievement("CgkI69-MotMIEAIQEA");
					SonarCocosHelper::GooglePlayServices::incrementAchievement("CgkI69-MotMIEAIQCA", 1);
				}
				nodeB->removeFromParentAndCleanup(true);
			}
		}
		else if (nodeA->getTag() == 30)
		{
			score = score + 1;
			__String *tempScore = __String::createWithFormat("%i", score);
			scoreLabel->setString(tempScore->getCString());
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/scoreSound.mp3");
			nodeA->removeFromParentAndCleanup(true);
			if (SonarCocosHelper::GooglePlayServices::isSignedIn)
			{
				SonarCocosHelper::GooglePlayServices::unlockAchievement("CgkI69-MotMIEAIQDw");
				SonarCocosHelper::GooglePlayServices::incrementAchievement("CgkI69-MotMIEAIQCg", 1);
				SonarCocosHelper::GooglePlayServices::incrementAchievement("CgkI69-MotMIEAIQCQ", 1);
			}
		}
		else if (nodeA->getTag() == 40)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/PowerUpCollected.mp3");
			nodeA->removeFromParentAndCleanup(true);
			powerUpBool = true;
			if (SonarCocosHelper::GooglePlayServices::isSignedIn)
			{
				SonarCocosHelper::GooglePlayServices::unlockAchievement("CgkI69-MotMIEAIQEA");
				SonarCocosHelper::GooglePlayServices::incrementAchievement("CgkI69-MotMIEAIQCA", 1);
			}
			this->scheduleOnce(schedule_selector(Endless::ScrollBackground), 3.0f);
		}
		else if (nodeA->getTag() == 50)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/speedboost.mp3");
			speed = true;
			nodeA->removeFromParentAndCleanup(true);
			if (SonarCocosHelper::GooglePlayServices::isSignedIn)
			{
				SonarCocosHelper::GooglePlayServices::unlockAchievement("CgkI69-MotMIEAIQEA");
				SonarCocosHelper::GooglePlayServices::incrementAchievement("CgkI69-MotMIEAIQCA", 1);
			}
			this->scheduleOnce(schedule_selector(Endless::StopSpeed), 4.5f);
		}
		else if (nodeA->getTag() == 60)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/ScoreBoost.mp3");
			score = score + 2;
			__String *tempScore = __String::createWithFormat("%i", score);
			scoreLabel->setString(tempScore->getCString());
			if (SonarCocosHelper::GooglePlayServices::isSignedIn)
			{
				SonarCocosHelper::GooglePlayServices::unlockAchievement("CgkI69-MotMIEAIQEA");
				SonarCocosHelper::GooglePlayServices::incrementAchievement("CgkI69-MotMIEAIQCA", 1);
			}
			nodeA->removeFromParentAndCleanup(true);
		}
	}

	if ((0x000001 == a->getCollisionBitmask() && 0x000002 == b->getCollisionBitmask() || 0x000001 == b->getCollisionBitmask() && 0x000002 == a->getCollisionBitmask()))
	{
		if (powerUpBool == false)
		{
			this->scheduleOnce(schedule_selector(Endless::activateGameOverScene), 1.5f);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/crashSound.mp3");
			Particles();
			move = false;
			Crash();
			if (SonarCocosHelper::GooglePlayServices::isSignedIn)
			{
				SonarCocosHelper::GooglePlayServices::unlockAchievement("CgkI69-MotMIEAIQDg");
				SonarCocosHelper::GooglePlayServices::submitScore("CgkI69-MotMIEAIQEw", score);
				SonarCocosHelper::GooglePlayServices::incrementAchievement("CgkI69-MotMIEAIQDQ", 1);
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/GameOver.mp3");
		}
	}
	return true;
}