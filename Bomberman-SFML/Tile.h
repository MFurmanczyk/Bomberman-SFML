#pragma once
#include "Pawn.h"
#include "Game.h"
#include "TextureManager.h"

class ATile : public APawn
{
public: 
	ATile();
	virtual void Draw() override;
	virtual void Update(const float& DeltaTime) override = 0;
};

class ATileController : public APawnController
{
public:
	ATileController() = default;
	virtual void Update(const float& DeltaTime) override {};
};

class AGroundTile : public ATile
{
public:
	AGroundTile() : ATile() { Sprite.setTexture(*(TTextureManager::Get("TileGround"))); };
	virtual void Update(const float& DeltaTime) override {};
};

class ASolidTile : public ATile
{
public:
	ASolidTile() : ATile() { Sprite.setTexture(*(TTextureManager::Get("TileSolid"))); };
	virtual void Update(const float& DeltaTime) override {};
};

class AExplodableTile : public ATile
{
public:
	AExplodableTile() : ATile() { Sprite.setTexture(*(TTextureManager::Get("TileExplodable"))); };
	virtual void Update(const float& DeltaTime) override {};
};