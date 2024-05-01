#pragma once
#include <vector>
#include "gameobject.h"
#include <memory>
#include <SFML/Window/Event.hpp>
#include "floor.h"
#include <array>

constexpr int floorCount = 20;

class World {
	std::array<std::unique_ptr<Floor>, floorCount> floors;
	int current_floor = 0;
	World() {};

public:
	static World& get_instance();
	void init();
	void reset();
	void update(sf::Event& event);
	void draw(sf::RenderWindow& window);
	Floor& get_current_floor() {
		return *floors[current_floor];
	}
	void change_floor(int floorNum);
	void descend() {
		change_floor(current_floor + 1);
	}
	void ascend() {
		change_floor(current_floor - 1);
	}
};