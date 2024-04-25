#pragma once
#include <vector>
#include "gameobject.h"
#include <memory>
#include <SFML/Window/Event.hpp>

class World {
	std::vector<std::unique_ptr<GameObject>> gameobjects;

public:
	void init();
	void update(sf::Event& event);
	void draw(sf::RenderWindow& window);
	void spawn_in_world(std::unique_ptr<GameObject> gameobject, sf::Vector2i position);
};