#pragma once
#include "component.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class Player : public Component {
public:
	Player(GameObject& gameobject) : Component(gameobject) {}
	void init() override;
	void update(sf::Event& event) override;
	void draw(sf::RenderWindow& window) override;
};