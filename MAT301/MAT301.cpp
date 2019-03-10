#include "pch.h"
#include "Game.h"

void main(int argc, char** argv[])
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Lab 1");
	Game game(&window);
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
			default:
				// don't handle other events
				break;
			}
		}
		game.handleInput();
		game.update();
		game.render();
	}
}