#pragma once

#include "pch.h"
#include "Game.h"

Game::Game(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	backTex.loadFromFile("gfx/Background.jpg");
	background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	background.setTexture(&backTex);
	background.setPosition(0, 0);

	neutralFaceTex.loadFromFile("gfx/Neutral.png");
	neutralFace.setSize(sf::Vector2f(400, 400));
	neutralFace.setTexture(&neutralFaceTex);
	neutralFace.setPosition(-20, 10);

}

Game::~Game()
{
}

void Game::update(float dt)
{
	background.update(dt);
	neutralFace.update(dt);
}

void Game::handleInput(float dt)
{
}

void Game::render()
{
	beginDraw();

	window->draw(background);
	window->draw(neutralFace);

	endDraw();
}

void Game::beginDraw()
{
	window->clear(sf::Color::Black);
}

void Game::endDraw()
{
	window->display();
}
