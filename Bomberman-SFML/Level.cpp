#include "Level.h"
#include "Tile.h"

GLevel::~GLevel()
{
	this->Clear();
}

bool GLevel::AddActor(AActor* Actor)
{
	if (Actor)
	{
		Actors.push_back(Actor);
		return true;
	}
	return false;
}

bool GLevel::RemoveActor(AActor* Actor)
{
	if (Actor)
	{
		auto ActorIt = std::find(Actors.begin(), Actors.end(), Actor);
		if (ActorIt != Actors.end())
		{
			delete *ActorIt;
			Actors.erase(ActorIt);
			return true;
		}
	}
	return false;
}

bool GLevel::ActorExists(AActor * Actor)
{
	if (Actor)
	{
		auto ActorIt = std::find(Actors.begin(), Actors.end(), Actor);
		if (ActorIt != Actors.end())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

void GLevel::Clear()
{
	for (auto Actor : Actors)
	{
		delete Actor;
	}
	return;
}

std::vector<AActor*> GLevel::GetCollidableTiles() const
{
	std::vector<AActor*> Tiles;
	for (auto Actor : Actors)
	{
		if (dynamic_cast<AExplodableTile*> (Actor) or dynamic_cast<ASolidTile*> (Actor))
		{
			Tiles.push_back(Actor);
		}
	}
	return Tiles;
}

std::vector<AActor*> GLevel::GetExplodableTiles() const
{
	std::vector<AActor*> Tiles;
	for (auto Actor : Actors)
	{
		if (dynamic_cast<AExplodableTile*> (Actor))
		{
			Tiles.push_back(Actor);
		}
	}
	return Tiles;
}

void GLevel::Update(const float & DeltaTime)
{
	for (auto Actor : Actors)
	{
		Actor->Update(DeltaTime);
	}
	return;
}

void GLevel::Draw()
{
	for (auto Actor : Actors)
	{
		Actor->Draw();
	}
	return;
}
