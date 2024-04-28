#include "gameobject.h"
#include "floor.h"
#include <typeinfo>
#include <type_traits>

void GameObject::init() {
    for (auto& component : components) {
        component->init();
    }
}
void GameObject::update(sf::Event& event) {
    for (auto& component : components) {
        component->update(event);
    }
}

void GameObject::draw(sf::RenderWindow& window) {
	for (auto& component : components) {
		component->draw(window);
	}

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

const std::vector<GameObject*> GameObject::get_collisions() const {
	std::vector<GameObject*> collisions;
	auto& allobjects = floor->get_gameobjects();
	for (auto& obj : allobjects) {
		if (obj.get() == this) {
			continue;
		}
		if (obj->get_position() == get_position()) {
			collisions.push_back(obj.get());
		}
	}
	return collisions;
}
