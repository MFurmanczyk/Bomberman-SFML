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

	void Clear(); //Cleanup the level but don't destroy level object

	void Update(const float& DeltaTime); //Updates all actors in the level
	void Draw(); //Draws all actors on screen

private:
	VActors Actors;
};