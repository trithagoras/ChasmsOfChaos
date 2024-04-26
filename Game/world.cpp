#include "world.h"
#include "gameobjectfactory.h"
#include <libtcod.hpp>
#include <iostream>

void World::init() {
	// init all floors in dungeon
	for (auto i = 0; i < floorCount; i++) {
		floors[i] = std::make_unique<Floor>(50, 50);
		floors[i]->init();
	}

	auto rng = TCODRandom();
	sf::Vector2i pos(rng.getInt(1, 48), rng.getInt(1, 48));
	while (!get_current_floor().walkable(pos)) {
		std::cout << "Player position was not in bounds. Retrying." << std::endl;
		pos = sf::Vector2i(rng.getInt(1, 48), rng.getInt(1, 48));
	}

	auto player = GameObjectFactory::get_instance().create_player();
	get_current_floor().spawn_object(std::move(player), pos);
}

void World::update(sf::Event& event) {
	floors[0]->update(event);
}

void World::draw(sf::RenderWindow& window) {
	floors[0]->draw(window);
}

