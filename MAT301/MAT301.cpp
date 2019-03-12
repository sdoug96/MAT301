#include "pch.h"
#include "Game.h"
#include "Input.h"

void main(int argc, char** argv[])
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "AI Response System");

	//Declare game objects
	Input input;

	Game game(&window, &input);

	//For delta time calculation
	sf::Clock clock;
	float deltaTime;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(0, 0,
					event.size.width, event.size.height)));
				break;
			case sf::Event::KeyPressed:
				input.setKeyDown(event.key.code);
				break;
			case sf::Event::KeyReleased:
				input.setKeyUp(event.key.code);
				break;
			case sf::Event::MouseMoved:
				input.setMousePosition(event.mouseMove.x, event.mouseMove.y);
				break;
			default:
				// don't handle other events
				break;
			}
		}

		//Calculate delta time
		deltaTime = clock.restart().asSeconds();

		game.handleInput(deltaTime);
		game.update(deltaTime);
		game.render();

		if (input.isKeyDown(sf::Keyboard::Escape))
		{
			window.close();
		}
	}
}