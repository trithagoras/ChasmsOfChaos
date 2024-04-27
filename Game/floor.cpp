#include "floor.h"
#include "gameobjectfactory.h"
#include "gamecolors.h"
#include <libtcod.hpp>
#include <iostream>

class MyCallback : public ITCODBspCallback {
	std::vector<std::pair<int, int>>& roomCenters;
public:
	MyCallback(std::vector<std::pair<int, int>>& centers) : roomCenters(centers) {}
	bool visitNode(TCODBsp* node, void* data) override {
		auto map = static_cast<TCODMap*>(data);
		if (node->isLeaf()) {
			int room_x = node->x + 1;
			int room_y = node->y + 1;
			int room_width = node->w - 2;
			int room_height = node->h - 2;

			if (room_width > 0 && room_height > 0) {
				for (int x = room_x; x < room_x + room_width; x++) {
					for (int y = room_y; y < room_y + room_height; y++) {
						map->setProperties(x, y, true, true);
					}
				}
				int center_x = room_x + room_width / 2;
				int center_y = room_y + room_height / 2;
				roomCenters.push_back({ center_x, center_y });  // Store the center
			}
		}
		return true;
	}
};


Floor::Floor(int width, int height) {
	this->width = width;
	this->height = height;
	this->floorShape = sf::RectangleShape(sf::Vector2f(width * 16, height * 16));
	this->floorShape.setFillColor(DARKMAROON);
}

void Floor::init() {
	map = std::make_unique<TCODMap>(width, height);
	auto bsp = TCODBsp(0, 0, width, height);
	bsp.splitRecursive(nullptr, 4, 5, 5, 1.5f, 1.5f);
	auto pcallback = std::make_unique<MyCallback>(roomCenters);
	bsp.traversePostOrder(pcallback.get(), map.get());

	// Connect rooms
	for (size_t i = 0; i < roomCenters.size() - 1; ++i) {
		drawCorridor(*map, roomCenters[i], roomCenters[i + 1]);
	}

	auto& objectFactory = GameObjectFactory::get_instance();
	for (auto row = 0; row < height; row++) {
		for (auto col = 0; col < width; col++) {
			if (!map->isWalkable(col, row)) {
				auto floorObj = objectFactory.create_wall();
				spawn_object(std::move(floorObj), col, row);
			}
		}
	}
}
void Floor::update(sf::Event& event) {
	for (auto& obj : gameobjects) {
		obj->update(event);
	}
}
void Floor::draw(sf::RenderWindow& window) {
	// draw floor color behind gameobjects
	window.draw(floorShape);

	for (auto& obj : gameobjects) {
		obj->draw(window);
	}
}

void Floor::spawn_object(std::unique_ptr<GameObject> gameobject, sf::Vector2i position) {
	spawn_object(std::move(gameobject), position.x, position.y);
}

void Floor::spawn_object(std::unique_ptr<GameObject> gameobject, int x, int y) {
	gameobject->set_position(x, y);
	gameobject->set_floor(this);
	this->gameobjects.push_back(std::move(gameobject));
}

void Floor::spawn_object_random(std::unique_ptr<GameObject> gameobject) {
	auto rng = TCODRandom::getInstance();
	sf::Vector2i pos(rng->getInt(1, width - 2), rng->getInt(1, height - 2));
	while (!walkable(pos)) {
		std::cout << gameobject->get_name() << " position was not in bounds. Retrying." << std::endl;
		pos = sf::Vector2i(rng->getInt(1, width - 2), rng->getInt(1, height - 2));
	}

	spawn_object(std::move(gameobject), pos);
}

void Floor::drawCorridor(TCODMap& map, std::pair<int, int> start, std::pair<int, int> end) {
	// Horizontal corridor
	int min_x = std::min(start.first, end.first);
	int max_x = std::max(start.first, end.first);
	for (int x = min_x; x <= max_x; x++) {
		map.setProperties(x, start.second, true, true);
	}

	// Vertical corridor
	int min_y = std::min(start.second, end.second);
	int max_y = std::max(start.second, end.second);
	for (int y = min_y; y <= max_y; y++) {
		map.setProperties(end.first, y, true, true);
	}
}