#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include "EngineCore.h"
#include "Actor.h"

class GLevel final
{
public:
	/*Inlevel actors' vector*/
	typedef std::vector<AActor*> VActors;
	GLevel() = default;
	~GLevel();

	bool AddActor(AActor* Actor); //Returns true if actor was added successfully
	bool RemoveActor(AActor* Actor); //Returns true if actor was removed successfully
	bool ActorExists(AActor* Actor); //Returns true if actor exists
	void Clear(); //Cleanup the level but don't destroy level object
	std::vector<AActor*> GetCollidableTiles() const; //Returns vector of tiles players able to collide
	std::vector<AActor*> GetExplodableTiles() const; //Returns vector of tiles players able to collide
	std::vector<AActor*> GetExplosions() const; // Returns vector of all explosions
	std::vector<AActor*> GetSpeedUps() const; //Returns vector of all speedups 

	void Update(const float& DeltaTime); //Updates all actors in the level
	void Draw(); //Draws all actors on screen

	bool PlayersAlive();

private:
	VActors Actors;
};