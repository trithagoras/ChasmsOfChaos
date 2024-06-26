#pragma once
#include <memory>
#include <vector>
#include "rooms/jail-10x10.h"
#include "rooms/moat-12x16.h"
#include "rooms/canyon-6x5.h"
#include "rooms/treasure-room-12x6.h"

enum ROOM_CONSTANTS {
	WALL = 0x0,
	WATER = 0x0000FF,
	FLOOR = 0xFFFFFF,
	SKELETON = 0xFF0000,
	ARTIFACT = 0xFFFF00,
	ITEM = 0x00FF00
};

class Room {
public:
	std::vector<std::vector<uint32_t>> layout;
	int width;
	int height;
	Room(int h, int w, std::vector<std::vector<uint32_t>> lay) : height(h), width(w), layout(std::move(lay)) { }
};


class GameRoomProvider {
	std::vector<Room> rooms;
	GameRoomProvider() {}
public:
	static GameRoomProvider& get_instance() {
		static GameRoomProvider instance;
		return instance;
	}

	void load_all_rooms() {
		add_room(Room(10, 10, jail_10x10));
		add_room(Room(12, 16, moat_12x16));
		add_room(Room(6, 5, canyon_6x5));
		add_room(Room(12, 6, treasure_room_12x6));
	}

	void add_room(const Room& room) {
		rooms.push_back(room);
	}

	const std::vector<Room>& get_rooms() const {
		return rooms;
	}
};