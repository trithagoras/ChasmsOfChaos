#pragma once
#include "component.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class PlayerC : public Component {
public:
	PlayerC(GameObject& gameobject) : Component(gameobject) {}
	void init() override;
	void update() override;
	void draw(sf::RenderWindow& window) override;
	int maxXp = 0, xp = 0;

private:
	void try_use_ladder(bool isDown);
	void try_grab_here();
};