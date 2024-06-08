#pragma once
#include "component.h"

class LadderC : public Component {
public:
	LadderC(GameObject& gameobject) : Component(gameobject) {}
	bool isDown = true;
	void init() override {}
	void update() override {}
	void draw(sf::RenderWindow& window) override {}
};