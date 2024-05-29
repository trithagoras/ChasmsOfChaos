#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class UI {
	UI() {};
	UI(const UI&) = delete;
	UI& operator=(const UI&) = delete;
	sf::View uiView;

public:
	static UI& get_instance();
	void initialize(const sf::RenderWindow& window);
	void draw_ui(sf::RenderWindow& window);
};