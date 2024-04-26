#include "floor.h"

void Floor::init() {
	map = std::make_unique<TCODMap>(width, height);
	// TODO: https://github.com/FaronBracy/RogueSharp/blob/main/RogueSharp/MapCreation/RandomRoomsMapCreationStrategy.cs
	// use powder style room list as arguments to ^^.
}
void Floor::update(sf::Event& event) {

}
void Floor::draw(sf::RenderWindow& window) {

}