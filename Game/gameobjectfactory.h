#pragma once
#include "player.h"
#include <memory>
#include "item.h"

class GameObjectFactory {
public:
	static GameObjectFactory& get_instance();
	std::unique_ptr<Player> create_player();
	std::unique_ptr<GameObject> create_wall();
};