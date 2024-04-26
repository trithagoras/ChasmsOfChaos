#pragma once
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class GameObject;	// forward declr

class Component {
protected:
	GameObject& gameobject;
	Component(GameObject& gameobject) : gameobject(gameobject) {}

public:
	virtual void init() = 0;
	virtual void update(sf::Event& event) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
};