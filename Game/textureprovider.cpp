#include "textureprovider.h"
#include <iostream>
#include <format>
#include <optional>

TextureProvider& TextureProvider::get_instance() {
	static TextureProvider instance;
	return instance;
}

sf::Texture& TextureProvider::load_texture(const std::string& name) {
	auto texture = std::make_unique<sf::Texture>();
	if (!texture->loadFromFile(std::format("Content/{}", name))) {
		std::cerr << "Failed to load texture" << std::endl;
		throw new std::runtime_error(std::format("Failed to load texture at path: Content/{}", name));
	}
	this->textures.emplace(name, std::move(texture));
	return *this->textures[name];
}

const sf::Texture& TextureProvider::get_texture(const std::string& name) {
	auto& texture = this->textures[name];
	if (texture) {
		return *this->textures[name];
	}
	throw new std::runtime_error(std::format("Texture does not exist or is not loaded: Content/{}", name));
}