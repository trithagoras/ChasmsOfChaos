#include "world.h"
#include "gameobjectfactory.h"

void World::init() {
	// init all floors in dungeon
	for (auto i = 0; i < floorCount; i++) {
		floors[i] = std::make_unique<Floor>(50, 50);	// TODO: make width/height a random range
		floors[i]->init();
	}

	auto player = GameObjectFactory::get_instance().create_player();
	get_current_floor().spawn_object(std::move(player), 32, 32);
}

void World::update(sf::Event& event) {
	floors[0]->update(event);
}

void World::draw(sf::RenderWindow& window) {
	floors[0]->draw(window);
}

