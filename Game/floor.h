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
	std::vector<std::pair<int, int>> roomCenters;
	void drawCorridor(TCODMap& map, std::pair<int, int> start, std::pair<int, int> end);
	sf::RectangleShape floorShape;
public:
	Floor(int width, int height);
	void init();
	void update(sf::Event& event);
	void draw(sf::RenderWindow& window);
	void spawn_object(std::unique_ptr<GameObject> gameobject, sf::Vector2i position);
	void spawn_object(std::unique_ptr<GameObject> gameobject, int x, int y);
	bool walkable(int x, int y) {
		return map->isWalkable(x, y);
	}
	bool walkable(sf::Vector2i pos) {
		return walkable(pos.x, pos.y);
	}
};