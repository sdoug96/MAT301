#include "pch.h"
#include "Game.h"
#include "Game2.h"
#include "Input.h"
#include <iostream>
#include <string>

using namespace std;

void main(int argc, char** argv[])
{
	int choice = -1;

	while (choice != 0)
	{
		cout << "Please choose what program you would like to use: " << endl << endl;
		cout << "Finite State Machine: (Press 1)" << endl;
		cout << "Reinforced Learning: (Press 2)" << endl;
		cout << "Quit: (Press 0)" << endl << endl;

		cin >> choice;
		cout << endl;

		if (choice == 1)
		{
			cout << "Finite state machine system selected!" << endl << endl << endl;

			sf::RenderWindow window(sf::VideoMode(1920, 1080), "AI Finite State Machine Response System");

			//Declare game objects
			Input input;
			Game game(&window, &input);

			//For delta time calculation
			sf::Clock clock;
			float deltaTime;

			//Window events (no input on objectives window)
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

		else if (choice == 2)
		{
			cout << "Reinforced learning system selected" << endl << endl << endl;

			sf::RenderWindow window(sf::VideoMode(1920, 1080), "AI Reinforced Learning Response System");

			//Declare game objects
			Input input;
			Game2 game2(&window, &input);

			//For delta time calculation
			sf::Clock clock;
			float deltaTime;

			//Window events (no input on objectives window)
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

				game2.handleInput(deltaTime);
				game2.update(deltaTime);
				game2.render();

				if (input.isKeyDown(sf::Keyboard::Escape))
				{
					window.close();
				}
			}
		}

		else if (choice == 0)
		{
			exit(0);
		}

		else
		{
		    cout << "Invalid choice, please choose again!" << endl << endl << endl;
		}
	}
}