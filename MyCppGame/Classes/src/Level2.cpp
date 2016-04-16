#include "Level2.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Level2::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = Level2::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());

	scene->addChild(layer);
	return scene;
}

void Level2::activatePauseScene(Ref *pSender)
{
	auto scene = PauseMenu::createScene();
	Director::getInstance()->pushScene(scene);
}

void Level2::activateLoadingScene(float dt)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/LevelCompleted.mp3");
	if (SonarCocosHelper::GooglePlayServices::isSignedIn)
	{
		SonarCocosHelper::GooglePlayServices::submitScore("CgkI69-MotMIEAIQAg", score);
	}
	auto scene = LoadingLevel3::createScene();
	Director::getInstance()->replaceScene(scene);
	//auto scene = GameOver::createScene();
	//Director::getInstance()->replaceScene(scene);
}

void Level2::activateGameOverScene(float dt)
{
	auto scene = GameOver::createScene();
	Director::getInstance()->replaceScene(scene);
}

void Level2::addBackGroundSprite(cocos2d::Size const & visibleSize, cocos2d::Point const & origin)
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

void Level2::ScrollBackground(float dt)
{
	powerUpBool = false;
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/PowerUpOver.mp3");
}

bool Level2::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//LevelLoader::getInstance()->load("data/Level2.json");
	CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
	m_gameState = GameStates::PlaceGunTower;
	score = 0;
	move = true;
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/scoreSound.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/crashSound.mp3");

	pauseItem =
		MenuItemImage::create("GameScreen/Pause_Button.png",
			"GameScreen/Pause_Button(Click).png",
			CC_CALLBACK_1(Level2::activatePauseScene, this));

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	powerUpBool = false;

	pauseItem->setPosition(22, 520);

	player = Player::create();
	player->setPosition(195, 125);
	player->setAnchorPoint(Point(0.5f, 0.55f));
	this->addChild(player,5);

	powerUp = PowerUp::create(1);
	powerUp->setPosition(195,1500);
	//this->addChild(powerUp);

	hud = HUD::create();
	hud->setPosition(340, 530);
	this->addChild(hud,6);

	label = Label::createWithTTF("Score:", "fonts/Marker Felt.ttf", 32);
	label->setPosition(320, 522);
	this->addChild(label,7);
	__String *tempScore = __String::createWithFormat("%i", score);
	scoreLabel = Label::createWithTTF(tempScore->getCString(), "fonts/Marker Felt.ttf",32);
	scoreLabel->setPosition(377, 522);
	this->addChild(scoreLabel,7);

	auto menu = Menu::create(pauseItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu,100);

	addBackGroundSprite(visibleSize, origin);
	createTowerBases();
	createCoins();
	createPolice();
	createAmbulances();
	createMTrucks();
	createTrucks();
	createBikes();


	/*auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(Level2::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Level2::onTouchMoved, this);*/

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
	auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(Level2::OnAcceleration, this));
	
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Level2::onContactBegin, this);
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

void Level2::update(float dt)
{
	if (move == true)
	{
		scoreLabel->setPositionY(scoreLabel->getPosition().y + 7.5);
		label->setPositionY(label->getPosition().y + 7.5);
		hud->setPositionY(hud->getPosition().y + 7.5);
		pauseItem->setPositionY(pauseItem->getPosition().y + 7.5);
		player->setPositionY(player->getPosition().y + 7.5);
	}
	if (player->getPosition().y > 7870)
	{
		float i = 2;
		//activateGameOverScene(i);
		activateLoadingScene(i);
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
	//Particles();
}

bool Level2::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event)
{
	CCLOG("onTouchBegan x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);
	return true;
}

void Level2::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event)
{
	if (move == true)
	{
		player->setPosition(touch->getLocation().x, player->getPosition().y);
	}
}

void Level2::Particles()
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

void Level2::Crash()
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

void Level2::OnAcceleration(cocos2d::CCAcceleration* pAcceleration, cocos2d::Event * event)
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

void Level2::createTowerBases()
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_textureAtlasImageFile);

	for (int i = 9; i < 17; i++)
	{
		TowerBase * base = TowerBase::create(Vec2(ptr->m_towerBaseX[i], ptr->m_towerBaseY[i]), m_gameState);
		m_towerBases.push_back(base);
		spritebatch->addChild(base, 1);
	}
	this->addChild(spritebatch, 1, TOWERS_SPRITE_BATCH);
}

void Level2::createCoins()
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_textureAtlasImageFile);

	for (int i = 23; i < 24; i++)
	{
		Coin * base = Coin::create(Vec2(ptr->m_coinPosX[i], ptr->m_coinPosY[i]), m_gameState);
		m_coins.push_back(base);
		spritebatch->addChild(base, 1);
	}
	this->addChild(spritebatch, 4, COINS_SPRITE_BATCH);
}

void Level2::createPolice()
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_textureAtlasImageFile);

	for (int i = 10; i < 17; i++)
	{
		Police * base = Police::create(Vec2(ptr->m_policePosX[i], ptr->m_policePosY[i]), m_gameState);
		m_polices.push_back(base);
		spritebatch->addChild(base, 1);
	}
	this->addChild(spritebatch, 1, COINS_SPRITE_BATCH);
}

void Level2::createAmbulances()
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_textureAtlasImageFile);

	for (int i = 4; i < 13; i++)
	{
		Ambulance * base = Ambulance::create(Vec2(ptr->m_ambulancePosX[i], ptr->m_ambulancePosY[i]), m_gameState);
		m_ambulances.push_back(base);
		spritebatch->addChild(base, 1);
	}
	this->addChild(spritebatch, 1, COINS_SPRITE_BATCH);
}

void Level2::createMTrucks()
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_textureAtlasImageFile);

	for (int i = 6; i < 14; i++)
	{
		MiniTruck * base = MiniTruck::create(Vec2(ptr->m_minitruckPosX[i], ptr->m_minitruckPosY[i]), m_gameState);
		m_miniTrucks.push_back(base);
		spritebatch->addChild(base, 1);
	}
	this->addChild(spritebatch, 1, COINS_SPRITE_BATCH);
}

void Level2::createTrucks()
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_textureAtlasImageFile);

	for (int i = 10; i < 17; i++)
	{
		Truck * base = Truck::create(Vec2(ptr->m_truckPosX[i], ptr->m_truckPosY[i]), m_gameState);
		m_trucks.push_back(base);
		spritebatch->addChild(base, 1);
	}
	this->addChild(spritebatch, 1, COINS_SPRITE_BATCH);
}

void Level2::createBikes()
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();

	for (int i = 3; i < 5; i++)
	{
		Bike * base = Bike::create(Vec2(ptr->m_bikePosX[i], ptr->m_bikePosY[i]), m_gameState);
		m_bikes.push_back(base);
		this->addChild(base, 1);
	}
	//this->addChild(base, 1, COINS_SPRITE_BATCH);
}

bool Level2::onContactBegin(cocos2d::PhysicsContact &contact)
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
				//int x = nodeB->getPosition().x;
				//int y = nodeB->getPosition().y;
				//std::shared_ptr<GameData> ptr = GameData::sharedGameData();
				//for (int i = 0; i < ptr->m_numberOfCoins; i++)
				//{
				//	if (m_coins[i]->getPosition().x == x && m_coins[i]->getPosition().y == y)
				//	{
				//		//m_coins[i]->setPositionX(4000);						
				//		//nodeB->removeFromPhysicsWorld();
				//		m_coins[i]->setPositionCoin();
				//		//nodeB->removeFromParentAndCleanup(true);
				//	}
				//}
				nodeB->removeFromParentAndCleanup(true);
				if (SonarCocosHelper::GooglePlayServices::isSignedIn)
				{
					SonarCocosHelper::GooglePlayServices::incrementAchievement("CgkI69-MotMIEAIQAA",1);
				}
			}

			else if (nodeB->getTag() == 40)
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/invisCollected.mp3");
				score = score + 1000;
				__String *tempScore = __String::createWithFormat("%i", score);
				scoreLabel->setString(tempScore->getCString());
				nodeB->removeFromParentAndCleanup(true);
				powerUpBool = true;
				this->scheduleOnce(schedule_selector(Level2::ScrollBackground), 4.0f);
			}
			else if (nodeA->getTag() == 60)
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/ScoreBoost.mp3");
				score = score + 100;
				__String *tempScore = __String::createWithFormat("%i", score);
				scoreLabel->setString(tempScore->getCString());
				nodeA->removeFromParentAndCleanup(true);
			}
		}
		else if (nodeA->getTag() == 30)
		{
			score = score + 10;
			__String *tempScore = __String::createWithFormat("%i", score);
			scoreLabel->setString(tempScore->getCString());
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/scoreSound.mp3");
			//int x = nodeA->getPosition().x;
			//int y = nodeA->getPosition().y;
			//std::shared_ptr<GameData> ptr = GameData::sharedGameData();
			//for (int i = 0; i < ptr->m_numberOfCoins; i++)
			//{
			//	if (m_coins[i]->getPosition().x == x && m_coins[i]->getPosition().y == y)
			//	{
			//		/*m_coins[i]->setPositionX(4000);
			//		m_coins[i]->setPositionY(4000);
			//		m_coins[i]->getPhysicsBody()->setAngularVelocity(10);*/
			//		//->removeFromParentAndCleanup(true);
			//		//nodeA->removeFromPhysicsWorld();
			//		m_coins[i]->setPositionCoin();
			//		//nodeA->removeFromParentAndCleanup(true);
			//	}
			//}
			nodeA->removeFromParentAndCleanup(true);
			if (SonarCocosHelper::GooglePlayServices::isSignedIn)
			{
				SonarCocosHelper::GooglePlayServices::incrementAchievement("CgkI69-MotMIEAIQAA", 1);
			}
		}
		else if (nodeA->getTag() == 40)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/invisCollected.mp3");
			score = score + 1000;
			__String *tempScore = __String::createWithFormat("%i", score);
			scoreLabel->setString(tempScore->getCString());
			nodeA->removeFromParentAndCleanup(true);
			powerUpBool = true;
			this->scheduleOnce(schedule_selector(Level2::ScrollBackground), 4.0f);
		}
		else if (nodeA->getTag() == 60)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/ScoreBoost.mp3");
			score = score + 100;
			__String *tempScore = __String::createWithFormat("%i", score);
			scoreLabel->setString(tempScore->getCString());
			nodeA->removeFromParentAndCleanup(true);
		}
	}

	if ((0x000001 == a->getCollisionBitmask() && 0x000002 == b->getCollisionBitmask() || 0x000001 == b->getCollisionBitmask() && 0x000002 == a->getCollisionBitmask()))
	{
		if (powerUpBool == false)
		{
			this->scheduleOnce(schedule_selector(Level2::activateGameOverScene), 1.491f);
			CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.85f);
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