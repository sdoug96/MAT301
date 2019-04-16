#pragma once

#include "pch.h"
#include "Game2.h"

Game2::Game2(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	if (!defaultFont.loadFromFile("font/interbureau.ttf"))
	{
		//something went wrong
	}

	//Initialise
	rewardValue = 0;
	rewardValString = "0";
	rewardVal = "";
	initBackAndFace();
	initLogosAndButtons();
	initText();

	//Add background noise
	audioMgr.addMusic("sfx/BarNoise.wav", "barNoise");
}

Game2::~Game2()
{
}

void Game2::update(float dt)
{
	//Play game music
	if (!hasStarted)
	{
		audioMgr.playMusicbyName("barNoise");
		hasStarted = true;
	}

	//Convert reward value int to string
	rewardValString = to_string(rewardValue);

	//Update text to converted int value
	AIRewardValText2.setString(rewardValString);
}

void Game2::handleInput(float dt)
{
	if (input->isKeyDown(sf::Keyboard::R))
	{
		input->setKeyUp(sf::Keyboard::R);
		rewardValue += 10;
		rewardVal = "reward";
	}

	if (input->isKeyDown(sf::Keyboard::P))
	{
		input->setKeyUp(sf::Keyboard::P);
		rewardValue -= 10;
		rewardVal = "punish";
	}

	//Option 1 (happy option) is chosen
	if (input->isKeyDown(sf::Keyboard::Num1))
	{
		input->setKeyUp(sf::Keyboard::Num1); //Set key up so it isnt held down
		updateHappyOptions(); //Update users responses
		updateAIOptions(); //Update AIs response
		lastClick = 1; //Update most recent user response
	}

	//Option 2 (sad option) is chosen
	if (input->isKeyDown(sf::Keyboard::Num2))
	{
		input->setKeyUp(sf::Keyboard::Num2); //Set key up so it isnt held down
		updateSadOptions(); //Update users responses
		updateAIOptions(); //Update AIs response
		lastClick = 2; //Update most recent user response
	}

	//Option 3 (angry option) is chosen
	if (input->isKeyDown(sf::Keyboard::Num3))
	{
		input->setKeyUp(sf::Keyboard::Num3); //Set key up so it isnt held down
		updateAngryOptions(); //Update users responses
		updateAIOptions(); //Update AIs response
		lastClick = 3; //Update most recent user response
	}

	//Option 4 (excited option) is chosen
	if (input->isKeyDown(sf::Keyboard::Num4))
	{
		input->setKeyUp(sf::Keyboard::Num4); //Set key up so it isnt held down
		updateExcitedOptions(); //Update users responses
		updateAIOptions(); //Update AIs response
		lastClick = 4; //Update most recent user response
	}
}

void Game2::render()
{
	beginDraw();

	///////Game Window//////////

	//Draw background and faces
	window->draw(background);
	window->draw(body);
	window->draw(face);

	//Draw text option indicators
	window->draw(happyLogo);
	window->draw(sadLogo);
	window->draw(angryLogo);
	window->draw(excitedLogo);
	window->draw(rewardLogo);
	window->draw(punishLogo);

	//Draw text boxes
	window->draw(AITextBox);
	window->draw(optionButton1);
	window->draw(optionButton2);
	window->draw(optionButton3);
	window->draw(optionButton4);
	window->draw(happyNum);
	window->draw(sadNum);
	window->draw(angryNum);
	window->draw(excitedNum);
	window->draw(rewardButton);
	window->draw(punishButton);
	window->draw(rewardLet);
	window->draw(punishLet);

	//Draw text
	window->draw(AIText);
	window->draw(textOption1);
	window->draw(textOption2);
	window->draw(textOption3);
	window->draw(textOption4);
	window->draw(AIMoodText1);
	window->draw(AIMoodText2);
	window->draw(AIRewardValText1);
	window->draw(AIRewardValText2);
	window->draw(rewardText);
	window->draw(punishText);

	endDraw();
}

void Game2::initBackAndFace()
{
	backTex.loadFromFile("gfx/Background.png");
	background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	background.setTexture(&backTex);
	background.setPosition(0, 0);

	bodyTexture.loadFromFile("gfx/Bartender.png");
	body.setSize(sf::Vector2f(350, 400));
	body.setTexture(&bodyTexture);
	body.setPosition(158, 263);

	neutralFaceTex.loadFromFile("gfx/Neutral.png");
	face.setSize(sf::Vector2f(200, 200));
	face.setTexture(&neutralFaceTex);
	face.setPosition(245, 240);

	happyFaceTex.loadFromFile("gfx/Happy.png");
	sadFaceTex.loadFromFile("gfx/Sad.png");
	angryFaceTex.loadFromFile("gfx/Angry.png");
	excitedFaceTex.loadFromFile("gfx/Excited.png");
}

void Game2::initLogosAndButtons()
{
	happyLogo.setRadius(20);
	happyLogo.setFillColor(sf::Color::Green);
	happyLogo.setPosition(1190, 263);

	sadLogo.setRadius(20);
	sadLogo.setFillColor(sf::Color::Blue);
	sadLogo.setPosition(1190, 353);

	angryLogo.setRadius(20);
	angryLogo.setFillColor(sf::Color::Red);
	angryLogo.setPosition(1190, 443);

	excitedLogo.setRadius(20);
	excitedLogo.setFillColor(sf::Color::Yellow);
	excitedLogo.setPosition(1190, 533);

	rewardLogo.setRadius(20);
	rewardLogo.setFillColor(sf::Color::Green);
	rewardLogo.setPosition(535, 365);

	punishLogo.setRadius(20);
	punishLogo.setFillColor(sf::Color::Red);
	punishLogo.setPosition(535, 465);

	textBoxTex.loadFromFile("gfx/Textbox.png");

	AITextBox.setSize(sf::Vector2f(800, 100));
	AITextBox.setTexture(&textBoxTex);
	AITextBox.setPosition(75, 725);

	optionButton1.setSize(sf::Vector2f(600, 75));
	optionButton1.setTexture(&textBoxTex);
	optionButton1.setPosition(1250, 250);

	optionButton2.setSize(sf::Vector2f(600, 75));
	optionButton2.setTexture(&textBoxTex);
	optionButton2.setPosition(1250, 340);

	optionButton3.setSize(sf::Vector2f(600, 75));
	optionButton3.setTexture(&textBoxTex);
	optionButton3.setPosition(1250, 430);

	optionButton4.setSize(sf::Vector2f(600, 75));
	optionButton4.setTexture(&textBoxTex);
	optionButton4.setPosition(1250, 520);

	rewardButton.setSize(sf::Vector2f(150, 75));
	rewardButton.setTexture(&textBoxTex);
	rewardButton.setPosition(600, 350);

	punishButton.setSize(sf::Vector2f(150, 75));
	punishButton.setTexture(&textBoxTex);
	punishButton.setPosition(600, 450);
}

void Game2::initText()
{
	AIText.setString("Hi, I am the bartender, would you like a drink?");
	AIText.setFont(defaultFont);
	AIText.setCharacterSize(40);
	AIText.setFillColor(sf::Color::Black);
	AIText.setPosition(AITextBox.getPosition().x + 20, AITextBox.getPosition().y + 20);

	textOption1.setString("I would love one!");
	textOption1.setFont(defaultFont);
	textOption1.setCharacterSize(25);
	textOption1.setFillColor(sf::Color::Black);
	textOption1.setPosition(optionButton1.getPosition().x + 20, optionButton1.getPosition().y + 15);

	textOption2.setString("I am really sad today");
	textOption2.setFont(defaultFont);
	textOption2.setCharacterSize(25);
	textOption2.setFillColor(sf::Color::Black);
	textOption2.setPosition(optionButton2.getPosition().x + 20, optionButton2.getPosition().y + 15);

	textOption3.setString("Your drinks look rubbish");
	textOption3.setFont(defaultFont);
	textOption3.setCharacterSize(25);
	textOption3.setFillColor(sf::Color::Black);
	textOption3.setPosition(optionButton3.getPosition().x + 20, optionButton3.getPosition().y + 15);

	textOption4.setString("Can I show you something?");
	textOption4.setFont(defaultFont);
	textOption4.setCharacterSize(25);
	textOption4.setFillColor(sf::Color::Black);
	textOption4.setPosition(optionButton4.getPosition().x + 20, optionButton4.getPosition().y + 15);

	rewardText.setString("Reward");
	rewardText.setFont(defaultFont);
	rewardText.setCharacterSize(30);
	rewardText.setFillColor(sf::Color::Black);
	rewardText.setPosition(rewardButton.getPosition().x + 20, rewardButton.getPosition().y + 15);

	punishText.setString("Punish");
	punishText.setFont(defaultFont);
	punishText.setCharacterSize(30);
	punishText.setFillColor(sf::Color::Black);
	punishText.setPosition(punishButton.getPosition().x + 20, punishButton.getPosition().y + 15);

	AIMoodText1.setString("Bartender Mood: ");
	AIMoodText1.setFont(defaultFont);
	AIMoodText1.setCharacterSize(50);
	AIMoodText1.setFillColor(sf::Color::Black);
	AIMoodText1.setPosition(50, 23);

	AIMoodText2.setString("Neutral");
	AIMoodText2.setFont(defaultFont);
	AIMoodText2.setCharacterSize(50);
	AIMoodText2.setFillColor(sf::Color::Black);
	AIMoodText2.setPosition(375, 23);

	AIRewardValText1.setString("Current Reward Value: ");
	AIRewardValText1.setFont(defaultFont);
	AIRewardValText1.setCharacterSize(50);
	AIRewardValText1.setFillColor(sf::Color::Black);
	AIRewardValText1.setPosition(1350, 850);

	AIRewardValText2.setString("0");
	AIRewardValText2.setFont(defaultFont);
	AIRewardValText2.setCharacterSize(50);
	AIRewardValText2.setFillColor(sf::Color::Black);
	AIRewardValText2.setPosition(1800, 850);

	happyNum.setString("1");
	happyNum.setFont(defaultFont);
	happyNum.setCharacterSize(35);
	happyNum.setFillColor(sf::Color::Black);
	happyNum.setPosition(happyLogo.getPosition().x + 15, happyLogo.getPosition().y - 5);

	sadNum.setString("2");
	sadNum.setFont(defaultFont);
	sadNum.setCharacterSize(35);
	sadNum.setFillColor(sf::Color::Black);
	sadNum.setPosition(sadLogo.getPosition().x + 15, sadLogo.getPosition().y - 5);

	angryNum.setString("3");
	angryNum.setFont(defaultFont);
	angryNum.setCharacterSize(35);
	angryNum.setFillColor(sf::Color::Black);
	angryNum.setPosition(angryLogo.getPosition().x + 15, angryLogo.getPosition().y - 5);

	excitedNum.setString("4");
	excitedNum.setFont(defaultFont);
	excitedNum.setCharacterSize(35);
	excitedNum.setFillColor(sf::Color::Black);
	excitedNum.setPosition(excitedLogo.getPosition().x + 15, excitedLogo.getPosition().y - 5);

	rewardLet.setString("R");
	rewardLet.setFont(defaultFont);
	rewardLet.setCharacterSize(35);
	rewardLet.setFillColor(sf::Color::Black);
	rewardLet.setPosition(rewardLogo.getPosition().x + 15, rewardLogo.getPosition().y - 5);

	punishLet.setString("P");
	punishLet.setFont(defaultFont);
	punishLet.setCharacterSize(35);
	punishLet.setFillColor(sf::Color::Black);
	punishLet.setPosition(punishLogo.getPosition().x + 15, punishLogo.getPosition().y - 5);
}

void Game2::updateAIOptions()
{
	int random = rand() % 4;

	switch (random)
	{
	case (0):
		AIText.setString("Thats really nice of you!");
		AIMoodText2.setString("Happy");
		AIMoodText1.setFillColor(sf::Color::Green);
		AIMoodText2.setFillColor(sf::Color::Green);
		face.setTexture(&happyFaceTex);
		break;

	case (1):
		AIText.setString("Thats so sad");
		AIMoodText2.setString("Sad");
		AIMoodText1.setFillColor(sf::Color::Blue);
		AIMoodText2.setFillColor(sf::Color::Blue);
		face.setTexture(&sadFaceTex);
		break;

	case (2):
		AIText.setString("You are making me angry");
		AIMoodText2.setString("Angry");
		AIMoodText1.setFillColor(sf::Color::Red);
		AIMoodText2.setFillColor(sf::Color::Red);
		face.setTexture(&angryFaceTex);
		break;

	case (3):
		AIText.setString("Really?!");
		AIMoodText2.setString("Excited");
		AIMoodText1.setFillColor(sf::Color::Yellow);
		AIMoodText2.setFillColor(sf::Color::Yellow);
		face.setTexture(&excitedFaceTex);
		break;
	}
}

void Game2::updateHappyOptions()
{
	int random = rand() % 5;

	//Choose a new random happy user response
	switch (random)
	{
	case (0):
		textOption1.setString("I would love a drink!");
		break;

	case (1):
		textOption1.setString("Your drinks look really good!");
		break;

	case (2):
		textOption1.setString("Its so hard to decide!");
		break;

	case (3):
		textOption1.setString("Everything looks so good!");
		break;

	case (4):
		textOption1.setString("I think I'll have a pint!");
		break;
	}
}

void Game2::updateSadOptions()
{
	int random = rand() % 5;

	//Choose a new random sad user response
	switch (random)
	{
	case (0):
		textOption2.setString("I am really sad today");
		break;

	case (1):
		textOption2.setString("I just dont feel like drinking");
		break;

	case (2):
		textOption2.setString("Maybe I'll have a water");
		break;

	case (3):
		textOption2.setString("This bar gets me down");
		break;

	case (4):
		textOption2.setString("I think I'm gonna go now");
		break;
	}
}

void Game2::updateAngryOptions()
{
	int random = rand() % 5;

	//Choose a new random angry user response
	switch (random)
	{
	case (0):
		textOption3.setString("Your drinks look rubbish");
		break;

	case (1):
		textOption3.setString("I bet these drinks are overpriced");
		break;

	case (2):
		textOption3.setString("This pub stinks");
		break;

	case (3):
		textOption3.setString("Do you even make any money here?");
		break;

	case (4):
		textOption3.setString("I might start a fight I'm that bored");
		break;
	}
}

void Game2::updateExcitedOptions()
{
	int random = rand() % 5;

	//Choose a new random excited user response
	switch (random)
	{
	case (0):
		textOption4.setString("Can I show you something?");
		break;

	case (1):
		textOption4.setString("I have an idea");
		break;

	case (2):
		textOption4.setString("It's for a new drink");
		break;

	case (3):
		textOption4.setString("I really think it would bring in customers");
		break;

	case (4):
		textOption4.setString("And here it is!");
		break;
	}
}

void Game2::beginDraw()
{
	window->clear(sf::Color::Black);
}

void Game2::endDraw()
{
	window->display();
}