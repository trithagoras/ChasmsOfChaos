#include "gameobjectfactory.h"
#include "textureprovider.h"
#include "gamecolors.h"
#include "contentprovider.h"
#include "utils.h"

GameObjectFactory& GameObjectFactory::get_instance() {
	static GameObjectFactory factory{};
	return factory;
}

std::unique_ptr<Player> GameObjectFactory::create_player() {
    auto player = std::make_unique<Player>();
    auto& spriteJson = ContentProvider::get_instance().get_sprite("player");
    auto& gameTexture = TextureProvider::get_instance().get_texture(spriteJson["textureName"]);
    auto textureRect = sf::IntRect(spriteJson["x"], spriteJson["y"], spriteJson["width"], spriteJson["height"]);
    auto playerSprite = std::make_unique<sf::Sprite>(sf::Sprite(gameTexture, textureRect));
    playerSprite->setScale(2, 2);
    playerSprite->setColor(sf::Color(str_to_hex(spriteJson["color"])));
    playerSprite->setPosition((sf::Vector2f)player->get_position());
    player->set_sprite(std::move(playerSprite));
    return player;
}