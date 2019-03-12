#pragma once

#include "pch.h"
#include "Game.h"

Game::Game(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	state = States::NEUTRAL;

	if (!defaultFont.loadFromFile("font/interbureau.ttf"))
	{
		//something went wrong
	}

	backTex.loadFromFile("gfx/Background.png");
	background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	background.setTexture(&backTex);
	background.setPosition(0, 0);

	neutralFaceTex.loadFromFile("gfx/Neutral.png");
	face.setSize(sf::Vector2f(400, 400));
	face.setTexture(&neutralFaceTex);
	face.setPosition(50, 100);

	happyFaceTex.loadFromFile("gfx/Happy.png");
	sadFaceTex.loadFromFile("gfx/Sad.png");
	angryFaceTex.loadFromFile("gfx/Angry.png");
	excitedFaceTex.loadFromFile("gfx/Excited.png");

	happyMeterRec.setFillColor(sf::Color::Green);
	happyMeterRec.setPosition(1375, 20);
	
	sadMeterRec.setFillColor(sf::Color::Blue);
	sadMeterRec.setPosition(1475, 20);

	angryMeterRec.setFillColor(sf::Color::Red);
	angryMeterRec.setPosition(1575, 20);

	excitedMeterRec.setFillColor(sf::Color::Yellow);
	excitedMeterRec.setPosition(1675, 20);

	happyMeterBack.setSize(sf::Vector2f(40, 70));
	happyMeterBack.setFillColor(sf::Color::Black);
	happyMeterBack.setPosition(happyMeterRec.getPosition().x - 10, 10);

	sadMeterBack.setSize(sf::Vector2f(40, 70));
	sadMeterBack.setFillColor(sf::Color::Black);
	sadMeterBack.setPosition(sadMeterRec.getPosition().x - 10, 10);

	angryMeterBack.setSize(sf::Vector2f(40, 70));
	angryMeterBack.setFillColor(sf::Color::Black);
	angryMeterBack.setPosition(angryMeterRec.getPosition().x - 10, 10);

	excitedMeterBack.setSize(sf::Vector2f(40, 70));
	excitedMeterBack.setFillColor(sf::Color::Black);
	excitedMeterBack.setPosition(excitedMeterRec.getPosition().x - 10, 10);

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

	textOption2.setString("No not really");
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

	audioMgr.addMusic("sfx/BarNoise.wav", "barNoise");
}

Game::~Game()
{
}

void Game::update(float dt)
{
	//Play game music
	if (!hasStarted)
	{
		audioMgr.playMusicbyName("barNoise");
		hasStarted = true;
	}

	updateHappyOptions(); //Update happy option text
	updateSadOptions(); //Update sad option text
	updateAngryOptions(); //Update angry option text
	updateExcitedOptions(); //Update excited option text

	handleMeters(); //Update meter values

	setState(); //Set states

	handleStates(); //Handle states
}

void Game::handleInput(float dt)
{
	//Option 1 (happy option) is chosen
	if (optionButton1.getGlobalBounds().contains(input->getMouseX(), input->getMouseY()) &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		happyClickCount += 1; //Increase happy click count by 1
		happyMeter += 10; //Increase happy meter value by 10
		input->setMouseX(optionButton1.getPosition().x - 1); //Move mouse so doesnt stay held on button
		input->setMouseY(optionButton1.getPosition().y - 1); //Move mouse so doesnt stay held on button
	}

	//Option 2 (sad option) is chosen
	if (optionButton2.getGlobalBounds().contains(input->getMouseX(), input->getMouseY()) &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sadMeter += 10; //Increase sad click count by 1
		sadClickCount += 1; //Increase sad meter value by 10
		input->setMouseX(optionButton2.getPosition().x - 1); //Move mouse so doesnt stay held on button
		input->setMouseY(optionButton2.getPosition().y - 1); //Move mouse so doesnt stay held on button
	}

	//Option 3 (angry option) is chosen
	if (optionButton3.getGlobalBounds().contains(input->getMouseX(), input->getMouseY()) &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		angryMeter += 10; //Increase angry click count by 1
		angryClickCount += 1; //Increase angry meter value by 10
		input->setMouseX(optionButton3.getPosition().x - 1); //Move mouse so doesnt stay held on button
		input->setMouseY(optionButton3.getPosition().y - 1); //Move mouse so doesnt stay held on button
	}

	//Option 4 (excited option) is chosen
	if (optionButton4.getGlobalBounds().contains(input->getMouseX(), input->getMouseY()) &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		excitedMeter += 10; //Increase excited click count by 1
		excitedClickCount += 1; //Increase excited meter value by 10
		input->setMouseX(optionButton4.getPosition().x - 1); //Move mouse so doesnt stay held on button
		input->setMouseY(optionButton4.getPosition().y - 1); //Move mouse so doesnt stay held on button
	}
}

void Game::render()
{
	beginDraw();

	//Draw background and faces
	window->draw(background);
	window->draw(face);

	//Draw meter outlines
	window->draw(happyMeterBack);
	window->draw(sadMeterBack);
	window->draw(angryMeterBack);
	window->draw(excitedMeterBack);

	//Draw meters
	window->draw(happyMeterRec);
	window->draw(sadMeterRec);
	window->draw(angryMeterRec);
	window->draw(excitedMeterRec);

	//Draw text option indicators
	window->draw(happyLogo);
	window->draw(sadLogo);
	window->draw(angryLogo);
	window->draw(excitedLogo);

	//Draw text boxes
	window->draw(AITextBox);
	window->draw(optionButton1);
	window->draw(optionButton2);
	window->draw(optionButton3);
	window->draw(optionButton4);

	//Draw text
	window->draw(AIText);
	window->draw(textOption1);
	window->draw(textOption2);
	window->draw(textOption3);
	window->draw(textOption4);
	window->draw(AIMoodText1);
	window->draw(AIMoodText2);

	endDraw();
}

void Game::handleMeters()
{
	//Update size of meters based on given responses
	happyMeterRec.setSize(sf::Vector2f(20, happyMeter));
	sadMeterRec.setSize(sf::Vector2f(20, sadMeter));
	angryMeterRec.setSize(sf::Vector2f(20, angryMeter));
	excitedMeterRec.setSize(sf::Vector2f(20, excitedMeter));

	//Dont allow emotion meters to exceed 50, reset meters if any reach 50 and set state to neutral
	if (happyMeter >= 50 || sadMeter >= 50 || angryMeter >= 50 || excitedMeter >= 50)
	{
		state = States::NEUTRAL;
		happyMeter = 0;
		sadMeter = 0;
		angryMeter = 0;
		excitedMeter = 0;
		happyClickCount = 0;
		sadClickCount = 0;
		angryClickCount = 0;
		excitedClickCount = 0;
	}
}

void Game::setState()
{
	//If happy meter is highest, make AI face happy
	if ((happyMeter > sadMeter) && (happyMeter > angryMeter) && (happyMeter > excitedMeter))
	{
		state = States::HAPPY;
	}

	//If sad meter is highest, make AI face sad
	if ((sadMeter > happyMeter) && (sadMeter > angryMeter) && (sadMeter > excitedMeter))
	{
		state = States::SAD;
	}

	//If angry meter is highest, make AI face angry
	if ((angryMeter > happyMeter) && (angryMeter > sadMeter) && (angryMeter > excitedMeter))
	{
		state = States::ANGRY;
	}

	//If excited meter is highest, make AI face excited
	if ((excitedMeter > happyMeter) && (excitedMeter > sadMeter) && (excitedMeter > angryMeter))
	{
		state = States::EXCITED;
	}
}

void Game::handleStates()
{
	if (state == States::NEUTRAL)
	{
		AIMoodText1.setFillColor(sf::Color::Black);
		AIMoodText2.setFillColor(sf::Color::Black);
		AIMoodText2.setString("Neutral");
		face.setTexture(&neutralFaceTex);
	}

	if (state == States::HAPPY)
	{
		AIMoodText1.setFillColor(sf::Color::Green);
		AIMoodText2.setFillColor(sf::Color::Green);
		AIMoodText2.setString("Happy");
		face.setTexture(&happyFaceTex);
	}

	if (state == States::SAD)
	{
		AIMoodText1.setFillColor(sf::Color::Blue);
		AIMoodText2.setFillColor(sf::Color::Blue);
		AIMoodText2.setString("Sad");
		face.setTexture(&sadFaceTex);
	}

	if (state == States::ANGRY)
	{
		AIMoodText1.setFillColor(sf::Color::Red);
		AIMoodText2.setFillColor(sf::Color::Red);
		AIMoodText2.setString("Angry");
		face.setTexture(&angryFaceTex);
	}

	if (state == States::EXCITED)
	{
		AIMoodText1.setFillColor(sf::Color::Yellow);
		AIMoodText2.setFillColor(sf::Color::Yellow);
		AIMoodText2.setString("Excited");
		face.setTexture(&excitedFaceTex);
	}
}

void Game::updateHappyOptions()
{
	switch (happyMeter)
	{
	case (0):
		textOption1.setString("I would love a drink!");
		break;

	case (10): 
		textOption1.setString("Your drinks look really good!");
		break;

	case (20): 
		textOption1.setString("Its so hard to decide!");
		break;

	case (30): 
		textOption1.setString("Everyting looks so good!");
		break;

	case (40): 
		textOption1.setString("I think I'll have a pint!");
		break;

	case (50): 
		textOption1.setString("I would a drink!");
		break;
	}
}

void Game::updateSadOptions()
{
	switch (sadMeter)
	{
	case (0):
		textOption2.setString("No not really");
		break;

	case (10):
		textOption2.setString("I just dont feel like drinking");
		break;

	case (20):
		textOption2.setString("Maybe I'll have a water");
		break;

	case (30):
		textOption2.setString("This bar gets me down");
		break;

	case (40):
		textOption2.setString("I think I'm gonna go now");
		break;

	case (50):
		textOption2.setString("No not really");
		break;
	}
}

void Game::updateAngryOptions()
{
	switch (angryMeter)
	{
	case (0):
		textOption3.setString("Your drinks look rubbish");
		break;

	case (10):
		textOption3.setString("I bet these drinks are overpriced");
		break;

	case (20):
		textOption3.setString("This pub stinks");
		break;

	case (30):
		textOption3.setString("Do you even make any money here?");
		break;

	case (40):
		textOption3.setString("I might start a fight I'm that bored");
		break;

	case (50):
		textOption3.setString("Your drinks look rubbish");
		break;
	}
}

void Game::updateExcitedOptions()
{
	switch (excitedMeter)
	{
	case (0):
		textOption4.setString("Can I show you something?");
		break;

	case (10):
		textOption4.setString("I have an idea");
		break;

	case (20):
		textOption4.setString("It's for a new drink");
		break;

	case (30):
		textOption4.setString("I really think it would bring in customers");
		break;

	case (40):
		textOption4.setString("And here it is!");
		break;

	case (50):
		textOption4.setString("Can I show you something?");
		break;
	}
}

void Game::beginDraw()
{
	window->clear(sf::Color::Black);
}

void Game::endDraw()
{
	window->display();
}