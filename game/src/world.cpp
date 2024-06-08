#include "world.h"
#include "gameobjectfactory.h"
#include <libtcod.hpp>
#include <iostream>
#include "playerc.h"
#include "ladderc.h"
#include <algorithm>
#include "ui.h"
#include <format>

void World::init() {
	for (int i = 0; i < floorCount; i++) {
		floors[i] = std::make_unique<Floor>(50, 50);
	}

	// init only first floor (lazy loading)
	floors[0]->init();

	auto upLadder = get_current_floor().get_up_ladder();
	get_current_floor().spawn_object(std::move(GameObjectFactory::get_instance().create_player()), upLadder->get_position());
}

void World::update() {
	get_current_floor().update();
}

void World::draw(sf::RenderWindow& window) {
	get_current_floor().draw(window);
	UI::get_instance().draw_ui(window);
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
	if (floorNum == current_floor) {
		return;
	}

	bool isGoingDown = floorNum > current_floor;

	auto pPlayer = get_current_floor().pop_player();
	current_floor += isGoingDown ? 1 : -1;

	// lazy load next floor
	if (!get_current_floor().is_initialized()) {
		get_current_floor().init();
	}

	// get this floors up ladder position
	auto it = std::find_if(get_current_floor().get_gameobjects().begin(), get_current_floor().get_gameobjects().end(), [isGoingDown](const std::unique_ptr<GameObject>& pobj) {
		auto comp = pobj->get_component<LadderC>();
		return comp != nullptr && comp->isDown == !isGoingDown;
	});

	auto pos = (*it)->get_position();
	get_current_floor().spawn_object(std::move(pPlayer), pos);
}