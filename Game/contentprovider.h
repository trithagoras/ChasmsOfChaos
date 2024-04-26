#pragma once
#include <nlohmann/json.hpp>
#include <SFML/Graphics/Sprite.hpp>

using json = nlohmann::json;

class ContentProvider {
	ContentProvider() {}
	ContentProvider(const ContentProvider&) = delete;
	ContentProvider& operator=(const ContentProvider&) = delete;

	std::map<std::string, std::unique_ptr<sf::Sprite>> sprites;

public:
	static ContentProvider& get_instance();
	void load_sprites();
	const sf::Sprite& get_sprite(const std::string& name);
};