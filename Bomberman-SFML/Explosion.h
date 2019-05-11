#pragma once
#include "Actor.h"
#include <vector>

class AExplosion final : public AActor
{
public:
	AExplosion();
	virtual ~AExplosion();
private: 
	std::vector<sf::Sprite> Sprite;
};