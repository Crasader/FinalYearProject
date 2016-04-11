#include "LevelLoader.h"
static LevelLoader* level = nullptr;
////////////////////////////////////////////////////////////
LevelLoader::LevelLoader(std::string const & filename) 
{
	loadJSONData(filename);
	m_document.Parse<0>(m_JSONData.c_str());	
	loadGameData();
}
LevelLoader::LevelLoader()
{
}

////////////////////////////////////////////////////////////
void LevelLoader::loadJSONData(std::string const & filename)
{
	m_JSONData.clear();

	auto fileUtils = cocos2d::FileUtils::getInstance();
	// Loads all the data in the file into a std::string.
	m_JSONData = fileUtils->getStringFromFile(filename);
}

void LevelLoader::load(std::string const & filename)
{
	loadJSONData(filename);
	m_document.Parse<0>(m_JSONData.c_str());
	loadGameData();
}

LevelLoader* LevelLoader::getInstance()
{
	if (!level) {
		level = new (std::nothrow)LevelLoader();
	}

	return level;
}


////////////////////////////////////////////////////////////
void LevelLoader::loadGameData()
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();

	Value::ConstMemberIterator it1 = m_document["global_settings"].MemberBegin();
	// Get value of "background_texture" 
	ptr->m_backgroundTextureFile = it1->value.GetString();
	// Get value of "texture_atlas_image_file" 
	it1++;
	ptr->m_backgroundTextureFile1 = it1->value.GetString();
	// Get value of "texture_atlas_image_file" 
	it1++;
	ptr->m_backgroundTextureFile2 = it1->value.GetString();
	// Get value of "texture_atlas_image_file" 
	it1++;
	ptr->m_backgroundTextureFile3 = it1->value.GetString();
	it1++;
	ptr->m_backgroundTextureFile4 = it1->value.GetString();
	it1++;
	ptr->m_backgroundTextureFile5 = it1->value.GetString();
	// Get value of "texture_atlas_image_file" 
	it1++;
	ptr->m_backgroundTextureFile6 = it1->value.GetString();
	// Get value of "texture_atlas_image_file" 
	it1++;
	ptr->m_textureAtlasImageFile = it1->value.GetString();
	// Get value of "texture_atlas_plist_file"
	it1++;
	ptr->m_textureAtlasPlistFile = it1->value.GetString();
	it1++;
	Value const & tower = it1->value; 
	assert(tower.IsObject());
	// Get the tower properties.
	ptr->m_towerBaseFile = tower["tower_base_file"].GetString();
	ptr->m_towerGunFile = tower["tower_gun_file"].GetString();
	ptr->m_coinFile = tower["coin_file"].GetString();
	ptr->m_police = tower["police_file"].GetString();
	ptr->m_truck = tower["truck_file"].GetString();
	ptr->m_ambulance = tower["ambulance_file"].GetString();
	ptr->m_mini_van = tower["mini_van_file"].GetString();
	ptr->m_mini_truck = tower["mini_truck_file"].GetString();
	ptr->m_taxi = tower["taxi_file"].GetString();
	ptr->m_towerWidth = tower["tower_width"].GetInt();
	ptr->m_towerHeight = tower["tower_height"].GetInt();
	ptr->m_coinWidth = tower["coin_width"].GetInt();
	ptr->m_coinHeight = tower["coin_height"].GetInt();
	ptr->m_firingDelay = tower["firing_delay"].GetInt();
	ptr->m_towerRotationSpeed = tower["tower_rotation_speed"].GetInt();

	// The "tower_rotation_origin" element is an object.
	Value const & towerRotationOrigin = tower["tower_rotation_origin"];
	ptr->m_towerRotationOriginX = towerRotationOrigin["x"].GetInt();
	ptr->m_towerRotationOriginY = towerRotationOrigin["y"].GetInt();
	ptr->m_numberOfTowerBases = tower["number_of_tower_bases"].GetInt();

	// The "tower_bases" element is an array.
	Value const & towerBases = tower["tower_bases"];
	// Iterate through the array.
	for (int i = 0; i < towerBases.Size(); i++) {
		ptr->m_towerBaseX[i] = towerBases[i]["x"].GetInt();
		ptr->m_towerBaseY[i] = towerBases[i]["y"].GetInt();
	}

	ptr->m_numberOfCoins = tower["number_of_coins"].GetInt();
	Value const & coinsBases = tower["my_coins"];
	//// Iterate through the array.
	for (int i = 0; i < coinsBases.Size(); i++) {
		ptr->m_coinPosX[i] = coinsBases[i]["x"].GetInt();
		ptr->m_coinPosY[i] = coinsBases[i]["y"].GetInt();
	}

	ptr->m_numberOfPolice = tower["number_of_police"].GetInt();
	Value const & policeBases = tower["my_police"];
	//// Iterate through the array.
	for (int i = 0; i < policeBases.Size(); i++) {
		ptr->m_policePosX[i] = policeBases[i]["x"].GetInt();
		ptr->m_policePosY[i] = policeBases[i]["y"].GetInt();
	}

	ptr->m_numberOfTruck = tower["number_of_truck"].GetInt();
	Value const & truckBases = tower["my_truck"];
	//// Iterate through the array.
	for (int i = 0; i < truckBases.Size(); i++) {
		ptr->m_truckPosX[i] = truckBases[i]["x"].GetInt();
		ptr->m_truckPosY[i] = truckBases[i]["y"].GetInt();
	}

	ptr->m_numberOfMiniTruck = tower["number_of_minitruck"].GetInt();
	Value const & minitruckBases = tower["my_minitruck"];
	//// Iterate through the array.
	for (int i = 0; i < minitruckBases.Size(); i++) {
		ptr->m_minitruckPosX[i] = minitruckBases[i]["x"].GetInt();
		ptr->m_minitruckPosY[i] = minitruckBases[i]["y"].GetInt();
	}

	ptr->m_numberOfAmbulance = tower["number_of_ambulance"].GetInt();
	Value const & ambulanceBases = tower["my_ambulance"];
	//// Iterate through the array.
	for (int i = 0; i < ambulanceBases.Size(); i++) {
		ptr->m_ambulancePosX[i] = ambulanceBases[i]["x"].GetInt();
		ptr->m_ambulancePosY[i] = ambulanceBases[i]["y"].GetInt();
	}

	// Move to the "projectile" element, which is another object.
	it1++;
	Value const & projectile = it1->value;
	ptr->m_projectileFile = projectile["projectile_file"].GetString();
	// The "projectile_centre" element is an object.	
	Value const & projectileCentre = projectile["projectile_centre"];
	ptr->m_projectileCentreX = projectileCentre["x"].GetInt();
	ptr->m_projectileCentreY = projectileCentre["y"].GetInt();
	// Get the remaining projectile attributes.
	ptr->m_maxNumProjectiles = projectile["max_num_projectiles"].GetInt();
	ptr->m_ttl = projectile["time_to_live"].GetInt();
	ptr->m_velocity = projectile["velocity"].GetInt();

	// Move to the "ai" element
	it1++;
	Value const & ai = it1->value;
	ptr->m_aiImageFile = ai["ai_image_file"].GetString();
	ptr->m_aiPlistFile = ai["ai_plist_file"].GetString();
	ptr->m_maxNumAI = ai["max_num_ai"].GetInt();
	ptr->m_spawnInterval = ai["ai_spawn_interval"].GetInt();
	ptr->m_aiScale = ai["ai_scale"].GetDouble();
	ptr->m_aiVelocity = ai["ai_velocity"].GetDouble();
	ptr->m_aiTimeDelay = ai["ai_time_delay"].GetInt();
	// The "ai_start_position" element is an object.
	Value const & aiStartPosition = ai["ai_start_position"];
	ptr->m_aiStartX = aiStartPosition["x"].GetInt();
	ptr->m_aiStartY = aiStartPosition["y"].GetInt();
	// The "ai_walking_spritesheet" element is an object.
	Value const & aiWalkingSpriteSheet = ai["ai_walking_spritesheet"];
	ptr->m_aiRows = aiWalkingSpriteSheet["rows"].GetInt();
	ptr->m_aiColumns = aiWalkingSpriteSheet["columns"].GetInt();
	ptr->m_aiWidth = aiWalkingSpriteSheet["width"].GetInt();
	ptr->m_aiHeight = aiWalkingSpriteSheet["height"].GetInt();
	// The "ai_waypoints" element is an array.
	Value const & aiWaypoints = ai["ai_waypoints"];
	// Iterate through the array.
	for (int i = 0; i < aiWaypoints.Size(); i++) {
		ptr->m_aiWPX[i] = aiWaypoints[i]["x"].GetInt();
		ptr->m_aiWPY[i] = aiWaypoints[i]["y"].GetInt();
	}
	ptr->m_numWaypoints = aiWaypoints.Size();
}
