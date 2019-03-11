#include "pch.h"
#include "GameObject.h"

GameObject::GameObject(const sf::Vector2f & size) : Sprites(size)
{
}


GameObject::~GameObject()
{
}

void GameObject::update(float dt)
{
	updateAABB();
}