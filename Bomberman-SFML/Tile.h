#pragma once
#include "Game.h"
#include "Pawn.h"

#include "TextureManager.h"

class ATile : public APawn
{
public: 
	ATile();
	virtual void Draw() override;
	virtual void Update(const float& DeltaTime) override = 0;
	inline virtual sf::FloatRect GetCollider() const = 0;
	sf::Vector2u GetSize() const { return this->Sprite.getTexture()->getSize(); };
};

class ATileController : public APawnController
{
public:
	ATileController() = default;
	virtual void Update(const float& DeltaTime) override {}; //TODO Controller for every type of tile
};

class AGroundTile : public ATile
{
public:
	AGroundTile() : ATile() 
	{ 
		Sprite.setTexture(*(TTextureManager::Get("TileGround"))); 
	};
	virtual void Update(const float& DeltaTime) override {};
	inline virtual sf::FloatRect GetCollider() const { return sf::FloatRect(); };
};

class ASolidTile : public ATile
{
public:
	ASolidTile() : ATile() 
	{ 
		Sprite.setTexture(*(TTextureManager::Get("TileSolid"))); 
	};
	virtual void Update(const float& DeltaTime) override
	{
	};
	inline virtual sf::FloatRect GetCollider() const override { return sf::FloatRect(Collider); };
	void SetCollider(sf::Vector2f _Position);

private:
	sf::FloatRect Collider;
};

class AExplodableTile : public ATile
{
public:
	AExplodableTile() : ATile()
	{
		Sprite.setTexture(*(TTextureManager::Get("TileExplodable")));

	};
	virtual ~AExplodableTile();
	virtual void Update(const float& DeltaTime) override 
	{
	};
	inline virtual sf::FloatRect GetCollider() const override { return sf::FloatRect(Collider); };
	void SetCollider(sf::Vector2f _Position);

private:
	sf::FloatRect Collider;
};
