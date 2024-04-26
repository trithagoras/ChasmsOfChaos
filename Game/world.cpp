#include "world.h"
#include "gameobjectfactory.h"
#include <libtcod.hpp>
#include <iostream>

void World::init() {
	// init all floors in dungeon
	for (auto i = 0; i < floorCount; i++) {
		floors[i] = std::make_unique<Floor>(50, 50);	// TODO: make width/height a random range
		floors[i]->init();
	}

	auto player = GameObjectFactory::get_instance().create_player();
	auto rng = TCODRandom();
	auto pref = &(*player);
	get_current_floor().spawn_object(std::move(player), rng.getInt(1, 48), rng.getInt(1, 48));

	while (!get_current_floor().walkable(pref->get_position())) {
		std::cout << "Player position was not in bounds. Retrying." << std::endl;
		pref->set_position(rng.getInt(1, 48), rng.getInt(1, 48));
	}
}

void World::update(sf::Event& event) {
	floors[0]->update(event);
}

void World::draw(sf::RenderWindow& window) {
	floors[0]->draw(window);
}

