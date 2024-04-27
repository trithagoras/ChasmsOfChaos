#include "gameobjectfactory.h"
#include "gamecolors.h"
#include "spritefactory.h"
#include "utils.h"
#include "player.h"
#include "contentprovider.h"
#include "itemc.h"

GameObjectFactory& GameObjectFactory::get_instance() {
	static GameObjectFactory factory{};
	return factory;
}

std::unique_ptr<GameObject> GameObjectFactory::create_player() {
    auto player = std::make_unique<GameObject>();
    player->add_component<Player>();
    auto sprite = std::make_unique<sf::Sprite>(SpriteFactory::get_instance().create_sprite("player"));
    player->set_name("Adventurer");
    player->set_sprite(std::move(sprite));
    return player;
}

std::unique_ptr<GameObject> GameObjectFactory::create_wall() {
    auto wall = std::make_unique<GameObject>();
    auto sprite = std::make_unique<sf::Sprite>(SpriteFactory::get_instance().create_sprite("wall"));
    wall->set_name("Wall");
    wall->set_sprite(std::move(sprite));
    return wall;
}

std::unique_ptr<GameObject> GameObjectFactory::create_item(const std::string& name) {
    auto obj = std::make_unique<GameObject>();
    auto item = std::make_unique<Item>(ContentProvider::get_instance().get_item(name));
    auto& comp = obj->add_component<ItemC>();

    comp.set_item(std::move(item));
    auto sprite = std::make_unique<sf::Sprite>(SpriteFactory::get_instance().create_sprite(comp.get_item().spriteName));
    obj->set_sprite(std::move(sprite));
    obj->set_name(name);

    return obj;
}