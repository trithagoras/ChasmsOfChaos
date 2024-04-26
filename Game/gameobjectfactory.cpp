#include "gameobjectfactory.h"
#include "textureprovider.h"
#include "gamecolors.h"
#include "spritefactory.h"
#include "utils.h"

GameObjectFactory& GameObjectFactory::get_instance() {
	static GameObjectFactory factory{};
	return factory;
}

std::unique_ptr<Player> GameObjectFactory::create_player() {
    auto player = std::make_unique<Player>();
    auto sprite = std::make_unique<sf::Sprite>(SpriteFactory::get_instance().create_sprite("player"));
    sprite->setScale(2, 2);
    sprite->setPosition((sf::Vector2f)player->get_position());
    player->set_sprite(std::move(sprite));
    return player;
}