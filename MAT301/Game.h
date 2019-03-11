#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GameObject.h"
#include "Input.h"

class Game 
{

public:

	Game(sf::RenderWindow* hwnd, Input* in);
	~Game();

	void update(float dt);
	void handleInput(float dt);
	void render();

private:

	sf::RenderWindow* window; //Window pointer
	Input* input; //Input pointer

	void beginDraw();
	void endDraw();

	int happyMeter = 0, sadMeter = 0, angryMeter = 0, excitedMeter = 0;

	GameObject background; //Background image game object
	GameObject neutralFace; //Neutral expression game object

	sf::Texture backTex; //Background image texture
	sf::Texture neutralFaceTex; //Neutral expression texture

};

