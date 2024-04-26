#include "contentprovider.h"
#include <iostream>
#include <fstream>
#include "utils.h"
#include "textureprovider.h"

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

void ContentProvider::load_sprites() {
	// Open the JSON file
	std::ifstream file("Content/sprites.json");
	json spriteList;
	file >> spriteList;

	// populating sprites
	for (const auto& item : spriteList) {
		std::string name = item["name"];
		auto& texture = TextureProvider::get_instance().get_texture(item["textureName"]);
		auto color = sf::Color(str_to_hex(item["color"]));
		auto textureRect = sf::IntRect(item["x"], item["y"], item["width"], item["height"]);
		this->sprites[name] = std::make_unique<sf::Sprite>(sf::Sprite(texture, textureRect));
		this->sprites[name]->setColor(color);
	}
}
