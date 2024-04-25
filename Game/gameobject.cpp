#include "gameobject.h"

void GameObject::draw(sf::RenderWindow& window) {
	this->sprite->setPosition((sf::Vector2f)this->get_position());
	window.draw(*this->sprite);
}

void GameObject::translate(sf::Vector2i dpos) {
	this->position += dpos;
}

void GameObject::translate(int dx, int dy) {
	this->position.x += dx;
	this->position.y += dy;
}
