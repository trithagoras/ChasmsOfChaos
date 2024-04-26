#pragma once
#include <nlohmann/json.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

using json = nlohmann::json;

class ContentProvider {
	ContentProvider() {}
	ContentProvider(const ContentProvider&) = delete;
	ContentProvider& operator=(const ContentProvider&) = delete;

	std::map<std::string, std::unique_ptr<sf::Sprite>> sprites;
	std::map<std::string, std::unique_ptr<sf::Texture>> textures;

	sf::Texture& load_texture(const std::string& name);

public:
	static ContentProvider& get_instance();
	void load_sprites();
	const sf::Sprite& get_sprite(const std::string& name);
	void load_textures();
	const sf::Texture& get_texture(const std::string& name);
};