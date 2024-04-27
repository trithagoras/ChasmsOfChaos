#pragma once
#include "gameobject.h"
#include <memory>
#include "item.h"

class GameObjectFactory {
public:
	static GameObjectFactory& get_instance();
	std::unique_ptr<GameObject> create_player();
	std::unique_ptr<GameObject> create_wall();
	std::unique_ptr<GameObject> create_item(const std::string& name);
	std::unique_ptr<GameObject> create_random_item();
};