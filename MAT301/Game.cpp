#pragma once

#include "pch.h"
#include "Game.h"

Game::Game(sf::RenderWindow* hwnd)
{
	window = hwnd;
}
Game::~Game()
{
}
void Game::update()
{
}
void Game::handleInput()
{
}
void Game::render()
{
	beginDraw();
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
