#pragma once
#include <SFML/Graphics/Sprite.hpp>

class SpriteWrapper {
public:
	sf::Sprite sprite;

	/// <summary>
	/// Whether the sprite 'wiggles' between the two states (animation)
	/// </summary>
	bool wiggly = false;

	/// <summary>
	/// Used only when wiggly = true
	/// </summary>
	std::string texturebasename;

	SpriteWrapper(sf::Sprite sprite, bool wiggly = false, const std::string& texturebasename = "") {
		this->sprite = sprite;
		this->wiggly = wiggly;
		this->texturebasename = texturebasename;
	}
};