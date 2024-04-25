#include "gameobjectfactory.h"
#include "textureprovider.h"
#include "gamecolors.h"

GameObjectFactory& GameObjectFactory::get_instance() {
	static GameObjectFactory factory{};
	return factory;
}

std::unique_ptr<Player> GameObjectFactory::create_player() {
    auto player = std::make_unique<Player>();
    auto& gameTexture = TextureProvider::get_instance().get_texture("game-tiles.png");
    auto playerSprite = std::make_unique<sf::Sprite>(sf::Sprite(gameTexture, sf::IntRect(28 * 16, 16, 16, 16)));
    playerSprite->setScale(2, 2);
    playerSprite->setColor(TAN);
    playerSprite->setPosition((sf::Vector2f)player->get_position());
    player->set_sprite(std::move(playerSprite));
    return player;
}