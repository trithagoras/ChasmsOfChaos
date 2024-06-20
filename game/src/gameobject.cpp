#include "gameobject.h"
#include "floor.h"
#include <typeinfo>
#include <type_traits>
#include "contentprovider.h"
#include <format>
#include "world.h"

void GameObject::init() {
    for (auto& component : components) {
        component->init();
    }
}
void GameObject::update() {
	for (size_t i = 0; i < components.size(); ++i) {
		components[i]->update();
		// recheck size to avoid oob access if elements were removed
		if (i >= components.size() - 1) break;
	}
}

void GameObject::draw(sf::RenderWindow& window) {
	for (auto& component : components) {
		component->draw(window);
	}

	auto [x, y] = get_position();
	this->sprite->sprite.setPosition(x * 16, y * 16);

	auto& world = World::get_instance();
	if (world.wigglejustchanged) {
		auto& content = ContentProvider::get_instance();
		auto texturename = std::vformat(this->sprite->texturebasename, std::make_format_args(world.wigglestate));
		this->sprite->sprite.setTexture(content.get_texture(texturename));
	}

	window.draw(this->sprite->sprite);
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

void GameObject::destroy() {
	this->floor->pop_gameobject(*this);
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
