#include "Tutorial.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Tutorial::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = Tutorial::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());

	scene->addChild(layer);
	return scene;
}

void Tutorial::activateTutorialInfo1(Ref *pSender)
{
	auto scene = TutorialInfo1::createScene();
	Director::getInstance()->pushScene(scene);
}

void Tutorial::activateTutorialInfo2(Ref *pSender)
{
	auto scene = TutorialInfo2::createScene();
	Director::getInstance()->pushScene(scene);
}

void Tutorial::activateTutorialInfo3(Ref *pSender)
{
	auto scene = TutorialInfo3::createScene();
	Director::getInstance()->pushScene(scene);
}

void Tutorial::activateTutorialInfo4(Ref *pSender)
{
	auto scene = TutorialInfo4::createScene();
	Director::getInstance()->pushScene(scene);
}

void Tutorial::activatePauseScene(Ref *pSender)
{
	auto scene = TutorialPause::createScene();
	Director::getInstance()->pushScene(scene);
}

void Tutorial::activateGameOverScene(float dt)
{
	auto scene = TutorialOver::createScene();
	Director::getInstance()->replaceScene(scene);
}

void Tutorial::addBackGroundSprite(cocos2d::Size const & visibleSize, cocos2d::Point const & origin)
{
	//add all backgrounds to the scene
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();

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

	backgroundSprite4 = Sprite::create
		(ptr->m_backgroundTextureFile);
	backgroundSprite4->setPosition(Point((visibleSize.width / 2) +
		origin.x, (visibleSize.height) + 6596));

	backgroundSprite5 = Sprite::create
		(ptr->m_backgroundTextureFile);
	backgroundSprite5->setPosition(Point((visibleSize.width / 2) +
		origin.x, (visibleSize.height) + 8596));

	this->addChild(backgroundSprite, -1);
	this->addChild(backgroundSprite2, -1);
	this->addChild(backgroundSprite3, -1);
	this->addChild(backgroundSprite4, -1);
	this->addChild(backgroundSprite5, -1);
}

void Tutorial::ScrollBackground(float dt)
{
	powerUpBool = false;
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/PowerUpOver.mp3");
}

void Tutorial::StopSpeed(float dt)
{
	speed = false;
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/PowerUpOver.mp3");
}

bool Tutorial::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//LevelLoader::getInstance()->load("data/Level2.json");
	CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
	m_gameState = GameStates::PlaceGunTower;
	move = true;
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/scoreSound.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/crashSound.mp3");

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	powerUpBool = false;

	pauseItem =
		MenuItemImage::create("GameScreen/Pause_Button.png",
			"GameScreen/Pause_Button(Click).png",
			CC_CALLBACK_1(Tutorial::activatePauseScene, this));

	pauseItem->setPosition(22, 520);

	auto menu = Menu::create(pauseItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 100);

	player = Player::create();
	player->setPosition(195, 125);
	player->setAnchorPoint(Point(0.5f, 0.55f));
	this->addChild(player,5);

	powerUp = PowerUp::create(2);
	powerUp->setPosition(195,5775);
	this->addChild(powerUp);

	addBackGroundSprite(visibleSize, origin);
	createTowerBases();
	createCoins();
	createPolice();
	createAmbulances();
	//createMTrucks();
	//createTrucks();
	//createBikes();

	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	auto screenSize = glview->getFrameSize();

	Device::setAccelerometerEnabled(true);
	auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(Tutorial::OnAcceleration, this));
	
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Tutorial::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

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

void Tutorial::update(float dt)
{
	if (move == true)
	{
		player->setPositionY(player->getPosition().y + 7.5);
		pauseItem->setPositionY(pauseItem->getPosition().y + 7.5);
	}
	if (speed == true && move == true)
	{
		player->setPositionY(player->getPosition().y + 3.0);
		pauseItem->setPositionY(pauseItem->getPosition().y + 3.0);
	}
	if (player->getPosition().y > 1500 && player->getPosition().y < 1525)
	{
		player->setPositionY(1526);
		activateTutorialInfo1(this);
	}

	if (player->getPosition().y > 3300 && player->getPosition().y < 3325)
	{
		player->setPositionY(3326);
		activateTutorialInfo2(this);
	}

	if (player->getPosition().y > 5150 && player->getPosition().y < 5160)
	{
		player->setPositionY(5161);
		activateTutorialInfo3(this);
	}

	if (player->getPosition().y > 7150 && player->getPosition().y < 7175)
	{
		player->setPositionY(7176);
		activateTutorialInfo4(this);
	}

	if (player->getPosition().y > 8350)
	{
		activateGameOverScene(1);
	}

	if (player->getPosition().x < 25)
	{
		player->setPositionX(26);
	}
	if (player->getPosition().x > 372)
	{
		player->setPositionX(371);
	}
	cameraTarget->setPositionY(player->getPosition().y + 115);
}

bool Tutorial::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event)
{
	CCLOG("onTouchBegan x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);
	return true;
}

void Tutorial::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event)
{
	if (move == true)
	{
		player->setPosition(touch->getLocation().x, player->getPosition().y);
	}
}

void Tutorial::Crash()
{
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

void Tutorial::OnAcceleration(cocos2d::CCAcceleration* pAcceleration, cocos2d::Event * event)
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

void Tutorial::createTowerBases()
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_textureAtlasImageFile);

	for (int i = 24; i < ptr->m_numberOfTowerBases; i++)
	{
		TowerBase * base = TowerBase::create(Vec2(ptr->m_towerBaseX[i], ptr->m_towerBaseY[i]), m_gameState);
		m_towerBases.push_back(base);
		spritebatch->addChild(base, 1);
	}
	this->addChild(spritebatch, 1, TOWERS_SPRITE_BATCH);
}

void Tutorial::createCoins()
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_textureAtlasImageFile);

	for (int i = 92; i < 104; i++)
	{
		Coin * base = Coin::create(Vec2(ptr->m_coinPosX[i], ptr->m_coinPosY[i]), m_gameState);
		m_coins.push_back(base);
		spritebatch->addChild(base, 1);
	}
	this->addChild(spritebatch, 4, COINS_SPRITE_BATCH);
}

void Tutorial::createPolice()
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_textureAtlasImageFile);

	for (int i = 24; i < ptr->m_numberOfPolice; i++)
	{
		Police * base = Police::create(Vec2(ptr->m_policePosX[i], ptr->m_policePosY[i]), m_gameState);
		m_polices.push_back(base);
		spritebatch->addChild(base, 1);
	}
	this->addChild(spritebatch, 1, COINS_SPRITE_BATCH);
}

void Tutorial::createAmbulances()
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_textureAtlasImageFile);

	for (int i = 22; i < ptr->m_numberOfAmbulance; i++)
	{
		Ambulance * base = Ambulance::create(Vec2(ptr->m_ambulancePosX[i], ptr->m_ambulancePosY[i]), m_gameState);
		m_ambulances.push_back(base);
		spritebatch->addChild(base, 1);
	}
	this->addChild(spritebatch, 1, COINS_SPRITE_BATCH);
}

void Tutorial::createMTrucks()
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_textureAtlasImageFile);

	for (int i = 0; i < 6; i++)
	{
		MiniTruck * base = MiniTruck::create(Vec2(ptr->m_minitruckPosX[i], ptr->m_minitruckPosY[i]), m_gameState);
		m_miniTrucks.push_back(base);
		spritebatch->addChild(base, 1);
	}
	this->addChild(spritebatch, 1, COINS_SPRITE_BATCH);
}

void Tutorial::createTrucks()
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_textureAtlasImageFile);

	for (int i = 0; i < 10; i++)
	{
		Truck * base = Truck::create(Vec2(ptr->m_truckPosX[i], ptr->m_truckPosY[i]), m_gameState);
		m_trucks.push_back(base);
		spritebatch->addChild(base, 1);
	}
	this->addChild(spritebatch, 1, COINS_SPRITE_BATCH);
}

void Tutorial::createBikes()
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();

	for (int i = 0; i < 3; i++)
	{
		Bike * base = Bike::create(Vec2(ptr->m_bikePosX[i], ptr->m_bikePosY[i]), m_gameState);
		m_bikes.push_back(base);
		this->addChild(base, 1);
	}
}

bool Tutorial::onContactBegin(cocos2d::PhysicsContact &contact)
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
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/scoreSound.mp3");
				nodeB->removeFromParentAndCleanup(true);
			}

			else if (nodeB->getTag() == 40)
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/invisCollected.mp3");
				nodeB->removeFromParentAndCleanup(true);
				powerUpBool = true;
				this->scheduleOnce(schedule_selector(Tutorial::ScrollBackground), 4.0f);
			}
			else if (nodeB->getTag() == 50)
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/speedboost.mp3");
				nodeB->removeFromParentAndCleanup(true);
				speed -= true;
				this->scheduleOnce(schedule_selector(Tutorial::StopSpeed), 3.0f);
			}
			else if (nodeB->getTag() == 60)
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/ScoreBoost.mp3");
				nodeB->removeFromParentAndCleanup(true);
			}
		}
		else if (nodeA->getTag() == 30)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/scoreSound.mp3");
			nodeA->removeFromParentAndCleanup(true);
		}
		else if (nodeA->getTag() == 40)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/invisCollected.mp3");
			nodeA->removeFromParentAndCleanup(true);
			powerUpBool = true;
			this->scheduleOnce(schedule_selector(Tutorial::ScrollBackground), 4.0f);
		}
		else if (nodeA->getTag() == 50)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/speedboost.mp3");
			nodeA->removeFromParentAndCleanup(true);
			speed -= true;
			this->scheduleOnce(schedule_selector(Tutorial::StopSpeed), 3.0f);
		}
		else if (nodeA->getTag() == 60)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/ScoreBoost.mp3");
			nodeA->removeFromParentAndCleanup(true);
		}
	}

	if ((0x000001 == a->getCollisionBitmask() && 0x000002 == b->getCollisionBitmask() || 0x000001 == b->getCollisionBitmask() && 0x000002 == a->getCollisionBitmask()))
	{
		if (powerUpBool == false)
		{
			this->scheduleOnce(schedule_selector(Tutorial::activateGameOverScene), 1.491f);
			CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.85f);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/crashSound.mp3");
			move = false;
			Crash();
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/GameOver.mp3");	
		}
	}
	return true;
}