#include "gameobject.h"
#include "floor.h"

void GameObject::init() {

}
void GameObject::update(sf::Event& event) {

}

void GameObject::draw(sf::RenderWindow& window) {
	auto [x, y] = get_position();
	this->sprite->setPosition(x * 16, y * 16);
	window.draw(*this->sprite);
}

void GameObject::translate(sf::Vector2i dpos) {
	this->translate(dpos.x, dpos.y);
}

void GameObject::translate(int dx, int dy) {
	auto newPos = sf::Vector2i(dx, dy) + position;
	if (this->floor->walkable(newPos)) {
		this->position = newPos;
	}
}
