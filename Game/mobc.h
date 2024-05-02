#pragma once
#include "component.h"

class MobC : public Component {
public:
	MobC(GameObject& gameobject) : Component(gameobject) {}
	void init() override {}
	void update(sf::Event& event) override {}
	void draw(sf::RenderWindow& window) override {}
};