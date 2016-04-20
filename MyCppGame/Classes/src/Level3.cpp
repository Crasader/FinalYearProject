#include "Level3.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Level3::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	auto layer = Level3::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());//sets the scene up with a physics world

	scene->addChild(layer);
	return scene;
}

void Level3::activatePauseScene(Ref *pSender)
{
	auto scene = PauseMenu::createScene();
	Director::getInstance()->pushScene(scene);
}

void Level3::activateLoadingScene(float dt)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/LevelCompleted.mp3");
	if (SonarCocosHelper::GooglePlayServices::isSignedIn)
	{
		SonarCocosHelper::GooglePlayServices::unlockAchievement("CgkI69-MotMIEAIQBg");
		SonarCocosHelper::GooglePlayServices::incrementAchievement("CgkI69-MotMIEAIQBw", 1);
		SonarCocosHelper::GooglePlayServices::submitScore("CgkI69-MotMIEAIQFA", Global::getInstance()->getScore());
	}
	auto scene = GameComplete::createScene();
	Director::getInstance()->replaceScene(scene);
}

void Level3::activateGameOverScene(float dt)
{
	auto scene = GameOver::createScene();
	Director::getInstance()->replaceScene(scene);
}

void Level3::addBackGroundSprite(cocos2d::Size const & visibleSize, cocos2d::Point const & origin)
{
	//add all backgrounds to the scene
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();

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

	backgroundSprite4 = Sprite::create
		(ptr->m_backgroundTextureFile3);
	backgroundSprite4->setPosition(Point((visibleSize.width / 2) +
		origin.x, (visibleSize.height) + 6596));

	backgroundSprite5 = Sprite::create
		(ptr->m_backgroundTextureFile3);
	backgroundSprite5->setPosition(Point((visibleSize.width / 2) +
		origin.x, (visibleSize.height) + 8596));

	this->addChild(backgroundSprite, -1);
	this->addChild(backgroundSprite2, -1);
	this->addChild(backgroundSprite3, -1);
	this->addChild(backgroundSprite4, -1);
	this->addChild(backgroundSprite5, -1);
}

void Level3::DeactivatePowerUp(float dt)
{
	powerUpBool = false;
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/PowerUpOver.mp3");
}

void Level3::StopSpeed(float dt)//stops the speed boost
{
	speed = false;
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/PowerUpOver.mp3");
}

bool Level3::init()
{
	if (!Layer::init())
	{
		return false;
	}
	CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
	m_gameState = GameStates::PlaceGunTower;
	score = 0;
	move = true;
	
	//preload the sound effects
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/scoreSound.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/crashSound.mp3");

	pauseItem =
		MenuItemImage::create("GameScreen/Pause_Button.png",
			"GameScreen/Pause_Button(Click).png",
			CC_CALLBACK_1(Level3::activatePauseScene, this));

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	powerUpBool = false;

	pauseItem->setPosition(22, 520);

	//creates the player object
	player = Player::create();
	player->setPosition(340, 125);
	player->setAnchorPoint(Point(0.5f, 0.55f));
	this->addChild(player,5);

	//creates the power up object
	powerUp = PowerUp::create(2);
	powerUp->setPosition(330,4050);
	this->addChild(powerUp);

	//creates the HUD object
	hud = HUD::create();
	hud->setPosition(333, 530);
	this->addChild(hud,6);

	//creates the label for the score thats displays in the top right hand corner
	label = Label::createWithTTF("Score:", "fonts/Marker Felt.ttf", 32);
	label->setPosition(312, 522);
	this->addChild(label,7);
	__String *tempScore = __String::createWithFormat("%i", Global::getInstance()->getScore());
	scoreLabel = Label::createWithTTF(tempScore->getCString(), "fonts/Marker Felt.ttf",32);
	scoreLabel->setPosition(369, 522);
	this->addChild(scoreLabel,7);

	auto menu = Menu::create(pauseItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu,100);

	//methods that create the backgrounds and objects in the level
	addBackGroundSprite(visibleSize, origin);
	createTowerBases();
	createCoins();
	createPolice();
	createAmbulances();
	createMTrucks();
	createTrucks();
	createBikes();

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

	//checks for movement on the device that will be use to move the car
	Device::setAccelerometerEnabled(true);
	auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(Level3::OnAcceleration, this));
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//checks for collisions between two objects with physics bodies
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Level3::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	//sets up the camera that will follow the player as it moves up the screen
	cameraTarget = Sprite::create();
	cameraTarget->setPositionX(visibleSize.width / 2);
	cameraTarget->setPositionY(player->getPosition().y - 115);
	this->scheduleUpdate();
	this->addChild(cameraTarget);
	camera = Follow::create(cameraTarget, Rect::ZERO);
	camera->retain();
	this->runAction(camera);
	return true;
}

void Level3::update(float dt)
{
	if (move == true)//moves everything up the screen at the same speed
	{
		scoreLabel->setPositionY(scoreLabel->getPosition().y + 7.5);
		label->setPositionY(label->getPosition().y + 7.5);
		hud->setPositionY(hud->getPosition().y + 7.5);
		pauseItem->setPositionY(pauseItem->getPosition().y + 7.5);
		player->setPositionY(player->getPosition().y + 7.5);
	}
	if (speed == true && move == true)
	{
		scoreLabel->setPositionY(scoreLabel->getPosition().y + 1.8);
		label->setPositionY(label->getPosition().y + 1.8);
		hud->setPositionY(hud->getPosition().y + 1.8);
		pauseItem->setPositionY(pauseItem->getPosition().y + 1.8);
		player->setPositionY(player->getPosition().y + 1.8);
	}
	if (player->getPosition().y > 9000)//checks to see if the player has finished the level
	{
		float i = 2;
		activateLoadingScene(i);
	}

	//checks to make sure the player stays withen the bounds of the screen
	if (player->getPosition().x < 25)
	{
		player->setPositionX(26);
	}
	if (player->getPosition().x > 372)
	{
		player->setPositionX(371);
	}

	//gets the camera to follow the players y postion  
	cameraTarget->setPositionY(player->getPosition().y + 115);
	//Particles();
}

bool Level3::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event)
{
	CCLOG("onTouchBegan x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);
	return true;
}

void Level3::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event)
{
	if (move == true)
	{
		player->setPosition(touch->getLocation().x, player->getPosition().y);
	}
}

void Level3::Particles()//particles that are use for emissions from the car
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

void Level3::Crash()// draws the animation for a crash and pasticles that fly out from there
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

void Level3::OnAcceleration(cocos2d::CCAcceleration* pAcceleration, cocos2d::Event * event)
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

void Level3::createTowerBases()//creates the taxis
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_textureAtlasImageFile);

	for (int i = 17; i < 24; i++)//loops thru the taxi for level 1
	{
		TowerBase * base = TowerBase::create(Vec2(ptr->m_towerBaseX[i], ptr->m_towerBaseY[i]), m_gameState);
		m_towerBases.push_back(base);
		spritebatch->addChild(base, 1);
	}
	this->addChild(spritebatch, 1, TOWERS_SPRITE_BATCH);
}

void Level3::createCoins()//creates the coins
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_textureAtlasImageFile);

	for (int i = 59; i < 92; i++)//loops thru the coins for level 3
	{
		Coin * base = Coin::create(Vec2(ptr->m_coinPosX[i], ptr->m_coinPosY[i]), m_gameState);
		m_coins.push_back(base);
		spritebatch->addChild(base, 1);
	}
	this->addChild(spritebatch, 4, COINS_SPRITE_BATCH);
}

void Level3::createPolice()//creates the police cars
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_textureAtlasImageFile);

	for (int i = 17; i < 24; i++)//loops thru the police cars for level 3
	{
		Police * base = Police::create(Vec2(ptr->m_policePosX[i], ptr->m_policePosY[i]), m_gameState);
		m_polices.push_back(base);
		spritebatch->addChild(base, 1);
	}
	this->addChild(spritebatch, 1, COINS_SPRITE_BATCH);
}

void Level3::createAmbulances()//creates the ambulances
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_textureAtlasImageFile);

	for (int i = 13; i < 22; i++)//loops thru the ambulances for level 3
	{
		Ambulance * base = Ambulance::create(Vec2(ptr->m_ambulancePosX[i], ptr->m_ambulancePosY[i]), m_gameState);
		m_ambulances.push_back(base);
		spritebatch->addChild(base, 1);
	}
	this->addChild(spritebatch, 1, COINS_SPRITE_BATCH);
}

void Level3::createMTrucks()//creates the mini trucks
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_textureAtlasImageFile);

	for (int i = 14; i < ptr->m_numberOfMiniTruck; i++)//loops thru the mini trucks for level 3
	{
		MiniTruck * base = MiniTruck::create(Vec2(ptr->m_minitruckPosX[i], ptr->m_minitruckPosY[i]), m_gameState);
		m_miniTrucks.push_back(base);
		spritebatch->addChild(base, 1);
	}
	this->addChild(spritebatch, 1, COINS_SPRITE_BATCH);
}

void Level3::createTrucks()//creates the trucks
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_textureAtlasImageFile);

	for (int i = 17; i < ptr->m_numberOfTruck; i++)//loops thru the trucks for level 3
	{
		Truck * base = Truck::create(Vec2(ptr->m_truckPosX[i], ptr->m_truckPosY[i]), m_gameState);
		m_trucks.push_back(base);
		spritebatch->addChild(base, 1);
	}
	this->addChild(spritebatch, 1, COINS_SPRITE_BATCH);
}

void Level3::createBikes()//creates the bkes
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();

	for (int i = 5; i < ptr->m_numberOfBike; i++)//loops thru the bikes for level 3
	{
		Bike * base = Bike::create(Vec2(ptr->m_bikePosX[i], ptr->m_bikePosY[i]), m_gameState);
		m_bikes.push_back(base);
		this->addChild(base, 1);
	}
	//this->addChild(base, 1, COINS_SPRITE_BATCH);
}

bool Level3::onContactBegin(cocos2d::PhysicsContact &contact)
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
				Global::getInstance()->setScore(10);
				__String *tempScore = __String::createWithFormat("%i", Global::getInstance()->getScore());
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
				CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(4.0f);
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/invisCollected.mp3");
				Global::getInstance()->setScore(30);
				__String *tempScore = __String::createWithFormat("%i", Global::getInstance()->getScore());
				scoreLabel->setString(tempScore->getCString());
				nodeB->removeFromParentAndCleanup(true);
				powerUpBool = true;
				if (SonarCocosHelper::GooglePlayServices::isSignedIn)
				{
					SonarCocosHelper::GooglePlayServices::unlockAchievement("CgkI69-MotMIEAIQEA");
					SonarCocosHelper::GooglePlayServices::incrementAchievement("CgkI69-MotMIEAIQCA", 1);
				}
				this->scheduleOnce(schedule_selector(Level3::DeactivatePowerUp), 4.0f);
			}
			else if (nodeB->getTag() == 50)
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(4.0f);
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/speedboost.mp3");
				nodeB->removeFromParentAndCleanup(true);
				Global::getInstance()->setScore(50);
				__String *tempScore = __String::createWithFormat("%i", Global::getInstance()->getScore());
				scoreLabel->setString(tempScore->getCString());
				speed -= true;
				if (SonarCocosHelper::GooglePlayServices::isSignedIn)
				{
					SonarCocosHelper::GooglePlayServices::unlockAchievement("CgkI69-MotMIEAIQEA");
					SonarCocosHelper::GooglePlayServices::incrementAchievement("CgkI69-MotMIEAIQCA", 1);
				}
				this->scheduleOnce(schedule_selector(Level3::StopSpeed), 2.0f);
			}
			else if (nodeB->getTag() == 60)
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(4.0f);
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/ScoreBoost.mp3");
				Global::getInstance()->setScore(100);
				__String *tempScore = __String::createWithFormat("%i", Global::getInstance()->getScore());
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
			Global::getInstance()->setScore(10);
			__String *tempScore = __String::createWithFormat("%i", Global::getInstance()->getScore());
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
			CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(4.0f);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/invisCollected.mp3");
			Global::getInstance()->setScore(30);
			__String *tempScore = __String::createWithFormat("%i", Global::getInstance()->getScore());
			scoreLabel->setString(tempScore->getCString());
			nodeA->removeFromParentAndCleanup(true);
			powerUpBool = true;
			if (SonarCocosHelper::GooglePlayServices::isSignedIn)
			{
				SonarCocosHelper::GooglePlayServices::unlockAchievement("CgkI69-MotMIEAIQEA");
				SonarCocosHelper::GooglePlayServices::incrementAchievement("CgkI69-MotMIEAIQCA", 1);
			}
			this->scheduleOnce(schedule_selector(Level3::DeactivatePowerUp), 4.0f);
		}

		else if (nodeA->getTag() == 50)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(4.0f);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/speedboost.mp3");
			nodeA->removeFromParentAndCleanup(true);
			Global::getInstance()->setScore(50);
			__String *tempScore = __String::createWithFormat("%i", Global::getInstance()->getScore());
			scoreLabel->setString(tempScore->getCString());
			speed -= true;
			if (SonarCocosHelper::GooglePlayServices::isSignedIn)
			{
				SonarCocosHelper::GooglePlayServices::unlockAchievement("CgkI69-MotMIEAIQEA");
				SonarCocosHelper::GooglePlayServices::incrementAchievement("CgkI69-MotMIEAIQCA", 1);
			}
			this->scheduleOnce(schedule_selector(Level3::StopSpeed), 2.0f);
		}

		else if (nodeA->getTag() == 60)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(4.0f);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/ScoreBoost.mp3");
			Global::getInstance()->setScore(100);
			__String *tempScore = __String::createWithFormat("%i", Global::getInstance()->getScore());
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
			this->scheduleOnce(schedule_selector(Level3::activateGameOverScene), 1.491f);
			CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.85f);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/crashSound.mp3");
			move = false;
			Crash();
			if (SonarCocosHelper::GooglePlayServices::isSignedIn)
			{
				SonarCocosHelper::GooglePlayServices::unlockAchievement("CgkI69-MotMIEAIQDg");
				SonarCocosHelper::GooglePlayServices::incrementAchievement("CgkI69-MotMIEAIQDQ", 1);
				SonarCocosHelper::GooglePlayServices::submitScore("CgkI69-MotMIEAIQFA", Global::getInstance()->getScore());
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/GameOver.mp3");	
		}
	}
	return true;
}