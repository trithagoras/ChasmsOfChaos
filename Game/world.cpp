#include "world.h"

void World::init() {
	// create and init first floor of dungeon

	for (auto& gameobject : this->gameobjects) {
		(*gameobject).init();
	}
}

void World::update(sf::Event& event) {
	for (auto& gameobject : this->gameobjects) {
		(*gameobject).update(event);
	}
}

void World::draw(sf::RenderWindow& window) {
	for (auto& gameobject : this->gameobjects) {
		(*gameobject).draw(window);
	}
}

void World::spawn_in_world(std::unique_ptr<GameObject> gameobject, sf::Vector2i position) {
	gameobject->set_position(position);
	this->gameobjects.push_back(std::move(gameobject));
}
