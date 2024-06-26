#pragma once
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
	bool initialized = false;
public:
	Floor(int width, int height);
	void init();
	void update();
	void draw(sf::RenderWindow& window);
	const GameObject& spawn_object(std::unique_ptr<GameObject> gameobject, sf::Vector2i position);
	const GameObject& spawn_object(std::unique_ptr<GameObject> gameobject, int x, int y);
	bool walkable(int x, int y) {
		return map->isWalkable(x, y);
	}
	bool walkable(sf::Vector2i pos) {
		return walkable(pos.x, pos.y);
	}
	const std::vector<std::unique_ptr<GameObject>>& get_gameobjects() const {
		return gameobjects;
	}
	bool is_initialized() const {
		return initialized;
	}

	GameObject* get_up_ladder() const;
	GameObject* get_down_ladder() const;
	GameObject* get_player() const;

	/// <summary>
	/// Ensures the object is spawned on a walkable tile. i.e. not in a wall.
	/// </summary>
	/// <param name="gameobject"></param>
	/// <returns>a reference to the new gameobject</returns>
	const GameObject& spawn_object_random(std::unique_ptr<GameObject> gameobject);
	std::unique_ptr<GameObject> pop_player();
	std::unique_ptr<GameObject> pop_gameobject(const GameObject& gameobject);
};