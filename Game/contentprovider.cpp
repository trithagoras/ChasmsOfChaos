#include "contentprovider.h"
#include <iostream>
#include <fstream>

ContentProvider& ContentProvider::get_instance() {
	static ContentProvider provider{};
	return provider;
}

const json& ContentProvider::get_sprite(const std::string& name) {
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
		this->sprites[name] = std::make_unique<json>(item);
	}
}