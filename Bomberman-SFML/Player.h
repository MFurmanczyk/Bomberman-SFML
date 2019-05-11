#pragma once
#include "Pawn.h"
#include "Game.h"
#include "Dynamite.h"

class APlayerController : public APawnController
{
public:
	APlayerController() : APawnController() {};

	virtual void Update(const float& DeltaTime) override;

private:
	void Move();

	void Plant();

private:
	AActor* Dynamite = nullptr;

	bool Setter = false;
};

class APlayer final : public APawn
{
public:
	APlayer();

	virtual void Draw() override;

private:
	sf::Texture Texture;
};


