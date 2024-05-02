#pragma once
#include "gameobject.h"
#include <memory>
#include "item.h"

class GameObjectFactory {
	GameObjectFactory() {}
	GameObjectFactory(const GameObjectFactory&) = delete;
	GameObjectFactory& operator=(const GameObjectFactory&) = delete;
public:
	static GameObjectFactory& get_instance();
	std::unique_ptr<GameObject> create_player();
	std::unique_ptr<GameObject> create_wall();
	std::unique_ptr<GameObject> create_item(const std::string& name);
	std::unique_ptr<GameObject> create_random_item();
	std::unique_ptr<GameObject> create_ladder(bool isDown);
	
	/// <summary>
	/// This allows you to choose the name of the object
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	std::unique_ptr<GameObject> create_gameobject(const std::string& name, const std::string& spriteName);
};