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

	// TODO: player should spawn on top of up ladder (for each floor that they enter)
	get_current_floor().spawn_object_random(std::move(GameObjectFactory::get_instance().create_player()));
	// just for fun, spawn a few items
	for (int i = 0; i < 10; i++) {
		get_current_floor().spawn_object_random(std::move(GameObjectFactory::get_instance().create_item("gold coin")));
	}
	for (int i = 0; i < 10; i++) {
		get_current_floor().spawn_object_random(std::move(GameObjectFactory::get_instance().create_item("empty vial")));
	}
}

void World::update(sf::Event& event) {
	floors[0]->update(event);
}

void World::draw(sf::RenderWindow& window) {
	floors[0]->draw(window);
}

