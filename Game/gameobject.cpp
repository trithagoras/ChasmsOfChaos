#include "gameobject.h"

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
	this->position += dpos;
}

void GameObject::translate(int dx, int dy) {
	this->position.x += dx;
	this->position.y += dy;
}
