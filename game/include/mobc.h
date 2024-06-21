#pragma once
#include "component.h"
#include "container.h"

class MobC : public Component {
public:
	MobC(GameObject& gameobject) : Component(gameobject) {}
	void init() override {}
	void update() override {}
	void draw(sf::RenderWindow& window) override {}
	int maxHp = 0, hp = 0, maxMp = 0, mp = 0, ac = 0;
	ItemContainer inventory;
};
