#pragma once
#include <memory>
#include <string>
#include <SFML/Graphics/Sprite.hpp>

class Item {
	std::string name;
	std::string description;
	std::unique_ptr<sf::Sprite> sprite;

public:
	Item(std::string name, std::string description, std::unique_ptr<sf::Sprite>(sprite)) {
		this->name = name;
		this->description = description;
		this->sprite = std::move(sprite);
	}
};