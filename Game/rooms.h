#pragma once
#include <memory>
#include <vector>
#include "jail-10x10.h"
#include "moat-12x16.h"

enum ROOM_CONSTANTS {
	WALL = 0x0,
	FLOOR = 0xFFFFFF,
	SKELETON = 0xFF0000,
	ARTIFACT = 0xFFFF00
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
	}

	void add_room(const Room& room) {
		rooms.push_back(room);
	}

	const std::vector<Room>& get_rooms() const {
		return rooms;
	}
};