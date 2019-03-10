#pragma once

#include <SFML/Graphics.hpp>

class Game 
{

public:

	Game(sf::RenderWindow* hwnd);
	~Game();
	void handleInput();
	void update();
	void render();

private:

	sf::RenderWindow* window;
	void beginDraw();
	void endDraw();

};

