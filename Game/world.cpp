#include "world.h"
#include "gameobjectfactory.h"
#include <libtcod.hpp>
#include <iostream>
#include "player.h"

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
	get_current_floor().update(event);
}

void World::draw(sf::RenderWindow& window) {
	get_current_floor().draw(window);
}

World& World::get_instance() {
	static World world{};
	return world;
}

void World::reset() {
	floors = std::array<std::unique_ptr<Floor>, floorCount>();
	current_floor = 0;
}

void World::change_floor(int floorNum) {
	if (floorNum > floorCount || floorNum < 0) {
		throw std::runtime_error(std::format("Invalid floornum {}", floorNum));
	}
	auto pPlayer = get_current_floor().pop_player();
	current_floor++;
	get_current_floor().spawn_object_random(std::move(pPlayer));
}