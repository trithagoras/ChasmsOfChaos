#pragma once
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "component.h"

class Floor;	// forward decl

class GameObject {
protected:
	std::string name;
	std::unique_ptr<sf::Sprite> sprite;	// TODO: this isn't guaranteed initialized
	sf::Vector2i position;
	Floor* floor;
	std::vector<std::unique_ptr<Component>> components;

public:
	GameObject() = default;
	virtual ~GameObject() = default;
	const sf::Vector2i get_position() const {
		return position;
	}
	void set_position(sf::Vector2i npos) {
		this->position = npos;
	}
	void set_position(int x, int y) {
		this->position = sf::Vector2i(x, y);
	}
	void set_sprite(std::unique_ptr<sf::Sprite> sprite) {
		this->sprite = std::move(sprite);
	}
	void set_floor(Floor* floor) {
		this->floor = floor;
	}
	const std::string& get_name() const {
		return name;
	}
	void set_name(const std::string& name) {
		this->name = name;
	}
	void translate(sf::Vector2i dpos);
	void translate(int dx, int dy);
	virtual void init();
	virtual void update(sf::Event& event);
	virtual void draw(sf::RenderWindow& window);
	const std::vector<GameObject*> get_collisions() const;

	// have to define template methods in .h file
	template <typename T>
	T& add_component() {
		static_assert(std::is_base_of<Component, T>::value, "T must be a Component");

		// if component already exists, return it
		for (auto& component : components) {
			if (typeid(*component) == typeid(T)) {
				return *static_cast<T*>(component.get());
			}
		}

		// otherwise, create new component, add it, and return it
		auto component = std::make_unique<T>(*this);
		T* result = component.get();
		components.push_back(std::move(component));
		return *result;
	}

	template <typename T>
	T* get_component() const {
		static_assert(std::is_base_of<Component, T>::value, "T must be a Component");

		for (const auto& component : components) {
			T* cast = dynamic_cast<T*>(component.get());
			if (cast) {
				return cast;
			}
		}
		return nullptr;  // nullptr if no component found
	}

	template <typename T>
	bool has_component() const {
		return get_component<T>() != nullptr;
	}
};
