#pragma once
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <libtcod.hpp>
#include <memory>
#include "gameobject.h"

class Floor {
	int width, height;
	std::unique_ptr<TCODMap> map;
	std::vector<std::unique_ptr<GameObject>> gameobjects;
public:
	Floor(int width, int height);
	void init();
	void update(sf::Event& event);
	void draw(sf::RenderWindow& window);
	void spawn_object(std::unique_ptr<GameObject> gameobject, sf::Vector2i position);
};