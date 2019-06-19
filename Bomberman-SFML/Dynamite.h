#pragma once
#include "Actor.h"
#include "Game.h"
#include "TextureManager.h"

class ADynamite : public APawn
{
public:
	ADynamite();
	virtual ~ADynamite() = default;

	virtual void Update(const float & DeltaTime) override;
	virtual void Draw() override;

private:

};

class ADynamiteController : public APawnController
{
public:

	ADynamiteController() = default;
	~ADynamiteController() = default;

	virtual void Update(const float& DeltaTime) override;

private:
	float ExplosionTime = 2.f;
};