#include "gameobjectfactory.h"
#include "gamecolors.h"
#include "spritefactory.h"
#include "utils.h"
#include "player.h"

GameObjectFactory& GameObjectFactory::get_instance() {
	static GameObjectFactory factory{};
	return factory;
}

std::unique_ptr<GameObject> GameObjectFactory::create_player() {
    auto player = std::make_unique<GameObject>();
    player->add_component<Player>();
    auto sprite = std::make_unique<sf::Sprite>(SpriteFactory::get_instance().create_sprite("player"));
    player->set_sprite(std::move(sprite));
    return player;
}

std::unique_ptr<GameObject> GameObjectFactory::create_wall() {
    auto wall = std::make_unique<GameObject>();
    auto sprite = std::make_unique<sf::Sprite>(SpriteFactory::get_instance().create_sprite("wall"));
    wall->set_sprite(std::move(sprite));
    return wall;
}