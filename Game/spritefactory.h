#pragma once
#include <string>
#include <memory>
#include <SFML/Graphics/Sprite.hpp>

class SpriteFactory {
	SpriteFactory() {}
	SpriteFactory(const SpriteFactory&) = delete;
	SpriteFactory& operator=(const SpriteFactory&) = delete;

public:
	static SpriteFactory& get_instance();
	sf::Sprite create_sprite(const std::string& name) const;
};