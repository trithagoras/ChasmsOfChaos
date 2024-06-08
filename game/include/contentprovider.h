#pragma once
#include <nlohmann/json.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include "item.h"
#include "spritewrapper.h"

using json = nlohmann::json;

class ContentProvider {
	ContentProvider() {}
	ContentProvider(const ContentProvider&) = delete;
	ContentProvider& operator=(const ContentProvider&) = delete;

	std::map<std::string, std::unique_ptr<SpriteWrapper>> sprites;
	std::map<std::string, std::unique_ptr<sf::Texture>> textures;
	std::map<std::string, std::unique_ptr<sf::Font>> fonts;
	std::map<std::string, std::unique_ptr<Item>> items;

	sf::Texture& load_texture(const std::string& name);

public:
	static ContentProvider& get_instance();
	void load_all_content();
	void load_sprites();
	const SpriteWrapper& get_sprite(const std::string& name) const;
	void load_textures();
	const sf::Texture& get_texture(const std::string& name) const;
	void load_items();
	const Item& get_item(const std::string& name) const;
	const Item& get_random_item() const;
	void load_fonts();
	const sf::Font& get_font(const std::string& name) const;
};