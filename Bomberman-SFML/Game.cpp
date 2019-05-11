#include "Game.h"

GGame::GGame() :
	Window(sf::VideoMode(800u, 600u, 32u), "Bomberman"),
	CurrentState(EState::Initializing),
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
	CurrentState = EState::Running;
	sf::Clock Clock;
	auto bman = new APlayer(); //TODO
	float DeltaTime = 1 / 60.f; //Frame duration
	while (CurrentState != EState::Ended)
	{
		float FrameStart = Clock.getElapsedTime().asSeconds(); //Frame start time... why?
		sf::Event event;
		Quit(event);
		Window.clear();
		Level->Update(DeltaTime);
		Level->Draw();
		Window.display();
		DeltaTime = Clock.getElapsedTime().asSeconds() - FrameStart; //Why this?
	}
	return; 
}

void Quit(sf::Event &event)
{
	auto& Game = GGame::Instantiate();
	while (Game.GetWindow().pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			Game.SetState(EState::Ended);
		}
	}
}
