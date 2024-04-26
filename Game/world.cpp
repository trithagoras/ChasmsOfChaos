#include "world.h"

void World::init() {
	// init all floors in dungeon
	for (auto i = 0; i < floorCount; i++) {
		floors[i] = std::make_unique<Floor>(30, 30);	// TODO: make width/height a random range
		floors[i]->init();
	}
}

void World::update(sf::Event& event) {
	floors[0]->update(event);
}

void World::draw(sf::RenderWindow& window) {
	floors[0]->draw(window);
}

