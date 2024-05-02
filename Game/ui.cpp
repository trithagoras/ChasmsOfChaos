#include "ui.h"
#include <SFML/Graphics/Text.hpp>
#include "contentprovider.h"
#include "world.h"
#include <format>
#include "spritefactory.h"
#include "gamecolors.h"
#include "mobc.h"
#include "playerc.h"

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

sf::Text make_text(const std::string& stext, int x = 0, int y = 0) {
	const auto& font = ContentProvider::get_instance().get_font("Consolas.ttf");

	sf::Text text(stext, font, 24);
	text.setPosition(sf::Vector2f(x, y));
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(1);
	return text;
}

void UI::draw_ui(sf::RenderWindow& window) {
	sf::View oldView(window.getView());

	auto& world = World::get_instance();
	auto& floor = world.get_current_floor();
	auto pPlayer = floor.get_player();
	const auto& playerComp = pPlayer->get_component<PlayerC>();
	const auto& mobComp = pPlayer->get_component<MobC>();
	auto& sprites = SpriteFactory::get_instance();

	auto& [width, height] = uiView.getSize();

	// set view to UI view before drawing
	window.setView(uiView);
	// ####################################################
	// bottom UI bar
	sf::RectangleShape bar(sf::Vector2f(width, 64));
	bar.setPosition(0, height - 64);
	bar.setFillColor(WOOD);
	window.draw(bar);

	// drawing bottom ui elements
	int i = 32;

	// floor
	auto flooricon = sprites.create_sprite("ladder icon");
	flooricon.setPosition(i, height - 48);
	flooricon.setScale(2, 2);
	window.draw(flooricon);
	window.draw(make_text(std::format("{:02}", world.get_floor_num() + 1), i + 40, height - 48));

	i += 128;

	// health
	auto hearticon = sprites.create_sprite("heart icon");
	hearticon.setPosition(i, height - 48);
	hearticon.setScale(2, 2);
	window.draw(hearticon);
	window.draw(make_text(std::format("{:02}/{:02}", mobComp->hp, mobComp->maxHp), i + 40, height - 48));

	i += 128;

	// mana
	auto manaicon = sprites.create_sprite("mana icon");
	manaicon.setPosition(i, height - 48);
	manaicon.setScale(2, 2);
	window.draw(manaicon);
	window.draw(make_text(std::format("{:02}/{:02}", mobComp->mp, mobComp->maxMp), i + 40, height - 48));

	i += 128;

	// AC
	auto acicon = sprites.create_sprite("shield icon");
	acicon.setPosition(i, height - 48);
	acicon.setScale(2, 2);
	window.draw(acicon);
	window.draw(make_text(std::format("{:02}", mobComp->ac), i + 40, height - 48));

	i += 128;

	// EXP
	auto expicon = sprites.create_sprite("exp icon");
	expicon.setPosition(i, height - 48);
	expicon.setScale(2, 2);
	window.draw(expicon);
	window.draw(make_text(std::format("{:04}/{:04}", playerComp->xp, playerComp->maxXp), i + 40, height - 48));

	// ####################################################
	// reset view to game view after UI drawing is done
	window.setView(oldView);
}