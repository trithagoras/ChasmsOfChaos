#include "ui.h"
#include <SFML/Graphics/Text.hpp>
#include "contentprovider.h"
#include "world.h"

void UI::initialize(const sf::RenderWindow& window) {
	sf::View uiView;
	uiView.setSize(window.getSize().x, window.getSize().y);
	uiView.setCenter(window.getSize().x / 2, window.getSize().y / 2);
	this->uiView = uiView;
}

UI& UI::get_instance() {
	static UI instance{};
	return instance;
}

void UI::draw_ui(sf::RenderWindow& window) {
	auto oldView = sf::View(window.getView());

	auto& floor = World::get_instance().get_current_floor();
	const auto& player = floor.get_player();

	// set view to UI view before drawing
	// ####################################################

	window.setView(uiView);
	sf::Text scoreText("Score: 100", ContentProvider::get_instance().get_font("Consolas.ttf"), 24);
	scoreText.setPosition(10, 10);
	window.draw(scoreText);

	// ####################################################
	// reset view to game view after UI drawing is done
	window.setView(oldView);
}