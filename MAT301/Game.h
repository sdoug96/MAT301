#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GameObject.h"
#include "Input.h"
#include "AudioManager.h"

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

	enum States
	{
		NEUTRAL,
		HAPPY,
		SAD,
		ANGRY,
		EXCITED,
		VERYHAPPY,
		VERYSAD,
		VERYANGRY,
		VERYEXCITED
	};

	States state;

	void handleMeters();
	void setState();
	void handleStates();

	void updateHappyOptions();
	void updateSadOptions();
	void updateAngryOptions();
	void updateExcitedOptions();

	void beginDraw();
	void endDraw();

	int happyMeter = 0, sadMeter = 0, angryMeter = 0, excitedMeter = 0;

	GameObject background; //Background image game object
	GameObject face; //Face game object
	GameObject AITextBox; //AIs text box game object
	GameObject optionButton1, optionButton2, optionButton3, optionButton4; //Option button game objects

	int happyClickCount = 0, sadClickCount = 0, angryClickCount = 0, excitedClickCount = 0; //Click counts for buttons

	int lastClick; //Last click to remember which option was selected last (1 = happy, 2 = sad, 3 = angry, 4 = excited)

	AudioManager audioMgr; //Manages game audio
	bool hasStarted;

	sf::Texture backTex; //Background image texture
	sf::Texture neutralFaceTex; //Neutral expression texture
	sf::Texture happyFaceTex; //Happy expression texture
	sf::Texture sadFaceTex; //Happy expression texture
	sf::Texture angryFaceTex; //Happy expression texture
	sf::Texture excitedFaceTex; //Happy expression texture
	sf::Texture textBoxTex; //Text box texture

	sf::Font defaultFont; //Font game object

	sf::Text AIText; //AI text game object
	sf::Text AIMoodText1; //AI mood text game objects
	sf::Text AIMoodText2; 
	sf::Text textOption1, textOption2, textOption3, textOption4; //Text option game objects

	sf::RectangleShape happyMeterBack, sadMeterBack, angryMeterBack, excitedMeterBack; //Meter background game objects

	sf::RectangleShape happyMeterRec, sadMeterRec, angryMeterRec, excitedMeterRec; //Meter game objects

	sf::CircleShape happyLogo, sadLogo, angryLogo, excitedLogo; //Indicator game objects
};

