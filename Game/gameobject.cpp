#include "gameobject.h"

void GameObject::draw(sf::RenderWindow& window) {
	auto pos = this->get_position();
	this->sprite->setPosition(pos.x, pos.y);
	window.draw(*this->sprite);
}

void GameObject::translate(sf::Vector2i dpos) {
	this->position += dpos;
}
void GameObject::translate(int dx, int dy) {
	this->position.x += dx;
	this->position.y += dy;
}
