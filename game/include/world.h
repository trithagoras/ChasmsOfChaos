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
	World(const World&) = delete;
	World& operator=(const World&) = delete;

public:
	int wigglestate = 0;	// alternates between 0 and 1
	bool wigglejustchanged = false;		// shitty optimization

	static World& get_instance();
	void init();
	void reset();
	void update(sf::Event& event);
	void draw(sf::RenderWindow& window);
	int get_floor_num() const {
		return current_floor;
	}
	Floor& get_current_floor() {
		return *floors[current_floor];
	}
	void change_floor(int floorNum);
	void descend() {
		if (current_floor == floorCount - 1) {
			return;
		}
		change_floor(current_floor + 1);
	}
	void ascend() {
		if (current_floor == 0) {
			return;
		}
		change_floor(current_floor - 1);
	}
};