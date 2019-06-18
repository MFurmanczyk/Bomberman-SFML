#include "Level.h"
#include "Tile.h"
#include "Speedup.h"
#include "Explosion.h"
#include "FirstPlayer.h"
#include "SecondPlayer.h"

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
			*ActorIt = nullptr;
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
		Actor = nullptr;
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

std::vector<AActor*> GLevel::GetExplosions() const
{
	std::vector<AActor*> Explosions;
	for (auto Actor : Actors)
	{
		if (dynamic_cast<AExplosion*> (Actor))
		{
			Explosions.push_back(Actor);
		}
	}
	return Explosions;
}

std::vector<AActor*> GLevel::GetSpeedUps() const
{
	std::vector<AActor*> Speedups;
	for (auto Actor : Actors)
	{
		if (dynamic_cast<ASpeedUp*> (Actor))
		{
			Speedups.push_back(Actor);
		}
	}
	return Speedups;
}

void GLevel::Update(const float & DeltaTime)
{
	for (auto Actor = 0; Actor < Actors.size(); Actor++)
	{
		Actors[Actor]->Update(DeltaTime);
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

bool GLevel::PlayersAlive()
{
	std::vector<AActor*> Players;
	for (auto Actor : Actors)
	{
		if (dynamic_cast<AFirstPlayer*> (Actor) or dynamic_cast<ASecondPlayer*> (Actor))
		{
			Players.push_back(Actor);
		}
	}
	auto FirstPlayer = dynamic_cast<AFirstPlayer*>(Players[0]);
	auto SecondPlayer = dynamic_cast<ASecondPlayer*>(Players[1]);

	for (auto Player : Players)
	{
		if (FirstPlayer->IsDead() or SecondPlayer->IsDead())
		{
			return false;
		}
	}
	return true;
}
