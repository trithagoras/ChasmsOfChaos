#include "contentprovider.h"
#include <iostream>
#include <fstream>
#include "utils.h"

ContentProvider& ContentProvider::get_instance() {
	static ContentProvider provider{};
	return provider;
}

const sf::Sprite& ContentProvider::get_sprite(const std::string& name) {
	auto& sprite = this->sprites[name];
	if (sprite) {
		return *this->sprites[name];
	}
	throw new std::runtime_error(std::format("Sprite does not exist or is not loaded: {}", name));
}

void ContentProvider::load_all_content() {
	load_sprites();
	load_textures();
	//load_items();
}

void ContentProvider::load_sprites() {
	// Open the JSON file
	std::ifstream file("Content/sprites.json");
	json spriteList;
	file >> spriteList;

	// populating sprites
	for (const auto& item : spriteList) {
		std::string name = item["name"];
		auto& texture = get_texture(item["textureName"]);
		auto color = sf::Color(str_to_hex(item["color"]));
		auto textureRect = sf::IntRect(item["x"], item["y"], item["width"], item["height"]);
		this->sprites[name] = std::make_unique<sf::Sprite>(sf::Sprite(texture, textureRect));
		this->sprites[name]->setColor(color);
	}
}

void ContentProvider::load_textures() {
	const std::vector<std::string> textures = { "game-tiles.png" };
	for (const auto& s : textures) {
		load_texture(s);
	}
}

sf::Texture& ContentProvider::load_texture(const std::string& name) {
	auto texture = std::make_unique<sf::Texture>();
	if (!texture->loadFromFile(std::format("Content/{}", name))) {
		std::cerr << "Failed to load texture" << std::endl;
		throw new std::runtime_error(std::format("Failed to load texture at path: Content/{}", name));
	}
	this->textures.emplace(name, std::move(texture));
	return *this->textures[name];
}

const sf::Texture& ContentProvider::get_texture(const std::string& name) {
	auto& texture = this->textures[name];
	if (texture) {
		return *this->textures[name];
	}
	throw new std::runtime_error(std::format("Texture does not exist or is not loaded: Content/{}", name));
}