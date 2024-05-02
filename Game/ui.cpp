#include "ui.h"
#include <SFML/Graphics/Text.hpp>
#include "contentprovider.h"
#include "world.h"
#include <format>
#include "spritefactory.h"

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

sf::Text make_text(const std::string& stext) {
	const auto& font = ContentProvider::get_instance().get_font("Consolas.ttf");

	sf::Text text(stext, font, 24);
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(1);
	return text;
}

void UI::draw_ui(sf::RenderWindow& window) {
	auto oldView = sf::View(window.getView());

	auto& world = World::get_instance();
	auto& floor = world.get_current_floor();
	const auto& player = floor.get_player();
	auto& sprites = 

	// set view to UI view before drawing
	// ####################################################

	window.setView(uiView);
	// TODO: this should be changed to ladder icon with rest of UI
	auto floorText = make_text(std::format("Floor: {}", world.get_floor_num()));
	floorText.setPosition(10, 10);
	window.draw(floorText);

	// health, AC, mana, EXP
	auto& hearticon = 

	// ####################################################
	// reset view to game view after UI drawing is done
	window.setView(oldView);
}