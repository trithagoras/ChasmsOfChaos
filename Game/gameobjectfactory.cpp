#include "gameobjectfactory.h"
#include "gamecolors.h"
#include "spritefactory.h"
#include "utils.h"
#include "playerc.h"
#include "contentprovider.h"
#include "itemc.h"
#include "ladderc.h"

GameObjectFactory& GameObjectFactory::get_instance() {
	static GameObjectFactory factory{};
	return factory;
}

std::unique_ptr<GameObject> GameObjectFactory::create_player() {
    auto player = std::make_unique<GameObject>();
    player->add_component<PlayerC>();
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

std::unique_ptr<GameObject> GameObjectFactory::create_random_item() {
    auto& item = ContentProvider::get_instance().get_random_item();
    return create_item(item.name);
}

std::unique_ptr<GameObject> GameObjectFactory::create_gameobject(const std::string& name, const std::string& spriteName) {
    auto obj = std::make_unique<GameObject>();
    auto sprite = std::make_unique<sf::Sprite>(SpriteFactory::get_instance().create_sprite(spriteName));
    obj->set_name(name);
    obj->set_sprite(std::move(sprite));
    return obj;
}

std::unique_ptr<GameObject> GameObjectFactory::create_ladder(bool isDown) {
    std::string s = isDown ? "down" : "up";
    auto obj = std::make_unique<GameObject>();
    auto sprite = std::make_unique<sf::Sprite>(SpriteFactory::get_instance().create_sprite(std::format("{} ladder", s)));
    obj->set_name(std::format("Ladder going {}", s));
    obj->set_sprite(std::move(sprite));
    auto& comp = obj->add_component<LadderC>();
    comp.isDown = isDown;
    return obj;
}