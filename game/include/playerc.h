#pragma once
#include "component.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class PlayerC : public Component {
public:
	PlayerC(GameObject& gameobject) : Component(gameobject) {}
	void init() override;
	void update(sf::Event& event) override;
	void draw(sf::RenderWindow& window) override;
	void try_use_ladder(bool isDown);
	int maxXp = 0, xp = 0;
};