#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <string>
#include <memory>
////////////////////////////////////////////////////////////
/// \brief A class that stores gameplay data
/// 
////////////////////////////////////////////////////////////


class GameData {
private:
	//Constructor
	GameData();

	static std::weak_ptr<GameData> m_instance;

	friend std::weak_ptr < GameData >;
	friend std::shared_ptr < GameData >;
public:
	//Get instance of singleton
	static std::shared_ptr<GameData> sharedGameData();

	std::string m_backgroundTextureFile;
	std::string m_backgroundTextureFile1;
	std::string m_backgroundTextureFile2;
	std::string m_backgroundTextureFile3;
	std::string m_backgroundTextureFile4;
	std::string m_textureAtlasImageFile;
	std::string m_textureAtlasPlistFile;
	// Tower base and tower related fields.
	std::string m_towerBaseFile;
	std::string m_towerGunFile;
	int m_towerWidth;
	int m_towerHeight;
	int m_firingDelay;
	int m_towerRotationSpeed;
	float m_towerRotationOriginX;
	float m_towerRotationOriginY;
	int m_numberOfTowerBases;

	float m_towerBaseX[10];
	float m_towerBaseY[10];

	//all the coin variables
	std::string m_coinFile;
	int m_coinWidth;
	int m_coinHeight;
	int m_numberOfCoins;

	float m_coinPosX[35];
	float m_coinPosY[35];

	std::string m_police;
	int m_numberOfPolice;
	float m_policePosX[25];
	float m_policePosY[25];

	std::string m_truck;
	int m_numberOfTruck;
	float m_truckPosX[25];
	float m_truckPosY[25];

	std::string m_ambulance;
	int m_numberOfAmbulance;
	float m_ambulancePosX[25];
	float m_ambulancePosY[25];

	std::string m_mini_van;
	int m_numberOfMiniVan;
	float m_minivanPosX[25];
	float m_minivanPosY[25];

	std::string m_mini_truck;
	int m_numberOfMiniTruck;
	float m_minitruckPosX[25];
	float m_minitruckPosY[25];

	std::string m_taxi;
	int m_numberOfTaxi;
	float m_taxiPosX[25];
	float m_taxiPosY[25];


	// Projectile related fields.
	std::string m_projectileFile;
	float m_projectileCentreX;
	float m_projectileCentreY;
	int m_maxNumProjectiles;
	int m_ttl;
	float m_velocity;

	// AI related fields.
	std::string m_aiImageFile;
	std::string m_aiPlistFile;
	int m_maxNumAI;
	int m_spawnInterval;
	float m_aiScale;
	float m_aiVelocity;
	int m_aiTimeDelay;
	int m_aiStartX;
	int m_aiStartY;
	// AI sprite sheet.
	int m_aiRows;
	int m_aiColumns;
	int m_aiWidth;
	int m_aiHeight;
	// AI Waypoints.
	int m_numWaypoints;
	float m_aiWPX[12];
	float m_aiWPY[12];
};

#endif