#include "contentprovider.h"
#include <iostream>
#include <fstream>
#include "utils.h"
#include <memory>
#include <libtcod.hpp>
#include <iterator>
#include <format>

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
	load_textures();
	load_sprites();
	load_fonts();

	// load game objects after sprites have loaded
	load_items();
}

void ContentProvider::load_sprites() {
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

void ContentProvider::load_items() {
	std::ifstream file("Content/items.json");
	json itemList;
	file >> itemList;

	// populating items
	for (const auto& i : itemList) {
		std::string name = i["name"];
		std::string description = i["description"];
		std::string spriteName = i["spriteName"];
		auto item = std::make_unique<Item>();
		item->name = name;
		item->description = description;
		item->spriteName = spriteName;
		this->items.emplace(name, std::move(item));
	}
}

const Item& ContentProvider::get_item(const std::string& name) {
	auto& item = this->items[name];
	if (item) {
		return *this->items[name];
	}
	throw new std::runtime_error(std::format("Item does not exist or is not loaded: ", name));
}

const Item& ContentProvider::get_random_item() {
	auto key = random_choose_map_key<std::string, std::unique_ptr<Item>>(items);
	return *items[key];
}

void ContentProvider::load_fonts() {
	// todo: this obviously is hardcoded to load a single font. Maybe need more in the future (maybe not?)
	auto font = std::make_unique<sf::Font>();
	if (!font->loadFromFile(std::format("Content/{}", "Pixeled.ttf"))) {
		std::cerr << "Failed to load font" << std::endl;
		throw new std::runtime_error(std::format("Failed to load texture at path: Content/{}", "Pixeled.ttf"));
	}
	this->fonts.emplace("Pixeled.ttf", std::move(font));
}

const sf::Font& ContentProvider::get_font(const std::string& name) {
	auto& font = this->fonts[name];
	if (font) {
		return *this->fonts[name];
	}
	throw new std::runtime_error(std::format("Font does not exist or is not loaded: ", name));
}