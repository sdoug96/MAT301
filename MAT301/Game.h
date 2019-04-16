#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GameObject.h"
#include "Input.h"
#include "AudioManager.h"
#include <iostream>

using namespace std;

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
	sf::RenderWindow* objectivesWindow; //Objectives window pointer

	Input* input; //Input pointer

	//Bartender emotional states
	enum States
	{
		NEUTRAL,
		HAPPY,
		SAD,
		ANGRY,
		EXCITED,
	};

	//Bartender emotional state
	States state;

	//Initialise main game objects
	void initBackAndFace();
	void initMeters();
	void initLogosAndButtons();
	void initText();

	//Update main game objects
	void handleMeters();
	void setState();
	void handleStates();

	//Update main game text options
	void updateAIOptions();

	void updateHappyOptions();
	void updateSadOptions();
	void updateAngryOptions();
	void updateExcitedOptions();

	void beginDraw();
	void endDraw();

	int happyMeter = 0, sadMeter = 0, angryMeter = 0, excitedMeter = 0; //Bartender emotion meters

	GameObject background; //Background image game object
	GameObject body; //Body game object
	GameObject face; //Face game object
	GameObject AITextBox; //AIs text box game object
	GameObject optionButton1, optionButton2, optionButton3, optionButton4; //Option button game objects

	int happyClickCount = 0, sadClickCount = 0, angryClickCount = 0, excitedClickCount = 0; //Click counts for buttons

	int lastClick; //Last click to remember which option was selected last (1 = happy, 2 = sad, 3 = angry, 4 = excited)

	AudioManager audioMgr; //Manages game audio
	bool hasStarted;

	sf::Texture backTex; //Background image texture
	sf::Texture bodyTexture; //Body texture
	sf::Texture neutralFaceTex; //Neutral expression texture
	sf::Texture happyFaceTex; //Happy expression texture
	sf::Texture sadFaceTex; //Sad expression texture
	sf::Texture angryFaceTex; //Angry expression texture
	sf::Texture excitedFaceTex; //Excited expression texture
	sf::Texture textBoxTex; //Text box texture

	sf::Font defaultFont; //Font game object

	sf::Text AIText; //AI text game object
	sf::Text AIMoodText1, AIMoodText2; //AI mood text game objects
	sf::Text textOption1, textOption2, textOption3, textOption4; //Text option game objects
	sf::Text happyNum, sadNum, angryNum, excitedNum; //Number indicator text objects

	sf::RectangleShape happyMeterBack, sadMeterBack, angryMeterBack, excitedMeterBack; //Meter background game objects

	sf::RectangleShape happyMeterRec, sadMeterRec, angryMeterRec, excitedMeterRec; //Meter game objects

	sf::CircleShape happyLogo, sadLogo, angryLogo, excitedLogo; //Indicator game objects
};

