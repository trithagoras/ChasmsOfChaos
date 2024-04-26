#pragma once
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <libtcod.hpp>
#include <memory>

class Floor {
	int width, height;
	std::unique_ptr<TCODMap> map;
public:
	Floor(int width, int height) {
		this->width = width;
		this->height = height;
	}
	void init();
	void update(sf::Event& event);
	void draw(sf::RenderWindow& window);
};