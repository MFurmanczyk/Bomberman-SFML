#pragma once
#include "Pawn.h"
#include "TextureManager.h"
#include "Game.h"

class AExplosion final : public APawn
{
public:
	AExplosion();
	virtual ~AExplosion() = default;

	virtual void Update(const float& DeltaTime) override;
	virtual void Draw() override;

};


class AExplosionController : public APawnController
{
public:
	AExplosionController() = default;
	~AExplosionController() = default;

	virtual void Update(const float& DeltaTime) override;

private:
	float Duration = 2.f;
};