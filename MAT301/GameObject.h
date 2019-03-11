#pragma once
#include "Sprites.h"

class GameObject : public Sprites
{
public:
	GameObject(const sf::Vector2f & size = sf::Vector2f(0, 0));
	~GameObject();

	void update(float dt);
};