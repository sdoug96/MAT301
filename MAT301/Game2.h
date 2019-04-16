#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include "GameObject.h"
#include "Input.h"
#include "AudioManager.h"
#include <iostream>

using namespace std;

class Game2
{

public:

	Game2(sf::RenderWindow* hwnd, Input* in);
	~Game2();

	void update(float dt);
	void handleInput(float dt);
	void render();

private:

	sf::RenderWindow* window; //Window pointer
	sf::RenderWindow* objectivesWindow; //Objectives window pointer

	Input* input; //Input pointer

	//Initialise main game objects
	void initBackAndFace();
	void initLogosAndButtons();
	void initText();

	//Update main game text options
	void updateAIOptions();

	void updateHappyOptions();
	void updateSadOptions();
	void updateAngryOptions();
	void updateExcitedOptions();

	void beginDraw();
	void endDraw();

	GameObject background; //Background image game object
	GameObject body; //Body game object
	GameObject face; //Face game object
	GameObject AITextBox; //AIs text box game object
	GameObject optionButton1, optionButton2, optionButton3, optionButton4; //Option button game objects
	GameObject rewardButton, punishButton; //Reward and punish button game objects

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
	sf::Text AIRewardValText1, AIRewardValText2; //AI reward value text game objects
	sf::Text textOption1, textOption2, textOption3, textOption4; //Text option game objects
	sf::Text happyNum, sadNum, angryNum, excitedNum, rewardLet, punishLet; //Number and letter indicator text game objects
	sf::Text rewardText, punishText; //Reward and punish text game objects

	sf::CircleShape happyLogo, sadLogo, angryLogo, excitedLogo, rewardLogo, punishLogo; //Indicator game objects

	int rewardValue; //AIs current reward value
	std::string rewardValString; //AIs current reward value to string
	std::string rewardVal; //Reward value in string form, reward or punish for AI to remember
};

