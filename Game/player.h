#pragma once
#include "gameobject.h"
#include <SFML/Window/Event.hpp>

class Player : public GameObject {
public:
	void init() override;
	void update(sf::Event& event) override;
	void draw(sf::RenderWindow& window) override;
};