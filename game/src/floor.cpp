#include "floor.h"
#include "gameobjectfactory.h"
#include "gamecolors.h"
#include <libtcod.hpp>
#include <iostream>
#include "rooms.h"
#include <iterator>
#include <algorithm>
#include "playerc.h"
#include "ladderc.h"

struct MyCallBackArgumentList {
	TCODMap* map;
	Floor* floor;
};

class MyCallback : public ITCODBspCallback {
	std::vector<std::pair<int, int>>& roomCenters;

public:
	MyCallback(std::vector<std::pair<int, int>>& centers) : roomCenters(centers) {}

	bool visitNode(TCODBsp* node, void* data) override {
		auto args = static_cast<MyCallBackArgumentList*>(data);
		auto map = args->map;
		auto floor = args->floor;
		auto& objfac = GameObjectFactory::get_instance();
		if (node->isLeaf()) {
			const auto& rooms = GameRoomProvider::get_instance().get_rooms();
			std::vector<Room> suitableRooms;

			// filter rooms that fit into the current node
			for (const auto& room : rooms) {
				if (room.width <= node->w && room.height <= node->h) {
					suitableRooms.push_back(room);
				}
			}

			// randomly select a suitable room if any are available
			if (!suitableRooms.empty()) {
				int index = TCODRandom::getInstance()->getInt(0, suitableRooms.size() - 1);
				const Room& selectedRoom = suitableRooms[index];

				int room_x = node->x + (node->w - selectedRoom.width) / 2;
				int room_y = node->y + (node->h - selectedRoom.height) / 2;

				for (int y = 0; y < selectedRoom.height; y++) {
					for (int x = 0; x < selectedRoom.width; x++) {
						bool walkable = selectedRoom.layout[y][x] != ROOM_CONSTANTS::WALL;
						map->setProperties(room_x + x, room_y + y, walkable, walkable);

						// if item (green)
						if (selectedRoom.layout[y][x] == ROOM_CONSTANTS::ITEM) {
							floor->spawn_object(std::move(objfac.create_random_item()), room_x + x, room_y + y);
						}

						// if water (blue)
						if (selectedRoom.layout[y][x] == ROOM_CONSTANTS::WATER) {
							floor->spawn_object(std::move(objfac.create_gameobject("Water", "water")), room_x + x, room_y + y);
							// TODO: ability to swim
							//map->setProperties(room_x + x, room_y + y, false, false);
						}
					}
				}

				roomCenters.push_back({ room_x + selectedRoom.width / 2, room_y + selectedRoom.height / 2 });
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
	if (initialized) {
		return;
	}
	map = std::make_unique<TCODMap>(width, height);
	auto bsp = TCODBsp(0, 0, width, height);
	bsp.splitRecursive(nullptr, 4, 5, 5, 1.5f, 1.5f);
	auto pcallback = std::make_unique<MyCallback>(roomCenters);
	auto args = MyCallBackArgumentList{};
	args.floor = this;
	args.map = map.get();
	bsp.traversePostOrder(pcallback.get(), &args);

	// connect rooms
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

	// place up/down ladders randomly
	auto& fac = GameObjectFactory::get_instance();
	auto upladder = fac.create_ladder(false);
	auto downladder = fac.create_ladder(true);
	const auto& upladderpos = spawn_object_random(std::move(upladder)).get_position();
	const auto& downladderpos = spawn_object_random(std::move(downladder)).get_position();
	if (upladderpos == downladderpos) {
		// todo: do something more here!
		std::cout << "Ladders spawned on each other." << std::endl;
	}

	initialized = true;
}

void Floor::update(sf::Event& event) {
	for (size_t i = 0; i < gameobjects.size(); ++i) {
		gameobjects[i]->update(event);
		// recheck size to avoid oob access if elements were removed (e.g. pop_player())
		if (i >= gameobjects.size() - 1) break;
	}
}
void Floor::draw(sf::RenderWindow& window) {
	// draw floor color behind gameobjects
	window.draw(floorShape);

	for (auto& obj : gameobjects) {
		obj->draw(window);
	}
}

const GameObject& Floor::spawn_object(std::unique_ptr<GameObject> gameobject, sf::Vector2i position) {
	return spawn_object(std::move(gameobject), position.x, position.y);
}

const GameObject& Floor::spawn_object(std::unique_ptr<GameObject> gameobject, int x, int y) {
	gameobject->set_position(x, y);
	gameobject->set_floor(this);
	this->gameobjects.push_back(std::move(gameobject));
	return *gameobjects.back();
}

const GameObject& Floor::spawn_object_random(std::unique_ptr<GameObject> gameobject) {
	auto rng = TCODRandom::getInstance();
	sf::Vector2i pos(rng->getInt(1, width - 2), rng->getInt(1, height - 2));
	while (!walkable(pos)) {
		std::cout << gameobject->get_name() << " position was not in bounds. Retrying." << std::endl;
		pos = sf::Vector2i(rng->getInt(1, width - 2), rng->getInt(1, height - 2));
	}

	return spawn_object(std::move(gameobject), pos);
}

std::unique_ptr<GameObject> Floor::pop_gameobject(const GameObject& gameobject) {
	auto it = std::find_if(gameobjects.begin(), gameobjects.end(), [&gameobject](std::unique_ptr<GameObject>& obj) {
		return obj.get() == &gameobject;
		});

	if (it != gameobjects.end()) {
		std::unique_ptr<GameObject> pObj = std::move(*it);
		gameobjects.erase(it);
		return pObj;
	}

	return nullptr;		// todo: is this enough?
}

std::unique_ptr<GameObject> Floor::pop_player() {
	auto it = std::find_if(gameobjects.begin(), gameobjects.end(), [](std::unique_ptr<GameObject>& obj) {
			return obj->has_component<PlayerC>();
		});
	
    if (it != gameobjects.end()) {
		std::unique_ptr<GameObject> pObj = std::move(*it);
        gameobjects.erase(it);
		return pObj;
    }

	return nullptr;		// todo: is this enough?
}

GameObject* Floor::get_up_ladder() const {
	const auto it = std::find_if(gameobjects.begin(), gameobjects.end(), [](const std::unique_ptr<GameObject>& obj) {
			const auto &comp = obj->get_component<LadderC>();
			return comp != nullptr && comp->isDown == false;
		});
	
    if (it != gameobjects.end()) {
		return (*it).get();
    }

	return nullptr;
}
GameObject* Floor::get_down_ladder() const {
	const auto it = std::find_if(gameobjects.begin(), gameobjects.end(), [](const std::unique_ptr<GameObject>& obj) {
			const auto &comp = obj->get_component<LadderC>();
			return comp != nullptr && comp->isDown;
		});
	
    if (it != gameobjects.end()) {
		return (*it).get();
    }

	return nullptr;
}

GameObject* Floor::get_player() const {
	const auto it = std::find_if(gameobjects.begin(), gameobjects.end(), [](const std::unique_ptr<GameObject>& obj) {
		return obj->has_component<PlayerC>();
		});

	if (it != gameobjects.end()) {
		return (*it).get();
	}

	return nullptr;
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