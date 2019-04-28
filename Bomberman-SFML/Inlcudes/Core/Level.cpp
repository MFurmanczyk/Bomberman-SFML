#include "Level.h"

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
		auto actorIt = std::find(Actors.begin(), Actors.end(), Actor);
		if (actorIt != Actors.end())
		{
			Actors.erase(actorIt);
			return true;
		}
	}
	return false;
}

void GLevel::Clear()
{
	for (auto Actor : Actors)
	{
		delete Actor;
	}
	return;
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
