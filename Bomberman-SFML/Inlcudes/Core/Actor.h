#pragma once

class AActor
{
public:
	AActor();
	virtual ~AActor();

	virtual void Draw() = 0;
	virtual void Update(float DeltaTime) = 0;
	inline virtual void SetLocation(const sf::Vector2f &Location);
protected:
	sf::Vector2f ActorLocation;
};