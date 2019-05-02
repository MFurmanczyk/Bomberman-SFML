#include "Game.h"

GGame::GGame() :
	Window(sf::VideoMode(800u, 600u, 32u), "Bomberman"),
	CurrentState(State::Initializing),
	Level(new GLevel),
	FrameLimit(60u)
{
	Window.setFramerateLimit(FrameLimit);
	return;
}

GGame::~GGame()
{
	if (Window.isOpen())
	{
		Window.close();
	}
	return;
}

void GGame::Run()
{
	CurrentState = State::Running;
	sf::Clock Clock;
	float DeltaTime = 1 / 60.f; //Frame duration
	auto bman = new APlayer();
	while (CurrentState != State::Ended)
	{
		float FrameStart = Clock.getElapsedTime().asSeconds(); //Frame start time... why?
		sf::Event event;
		while (Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				CurrentState = State::Ended;
			}
		}
		Window.clear();
		Level->Update(DeltaTime);
		Level->Draw();
		Window.display();
		DeltaTime = Clock.getElapsedTime().asSeconds() - FrameStart; //Why this?
	}
	return; 
}
