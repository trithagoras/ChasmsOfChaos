#pragma once
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>

class GameObject {
protected:
	std::unique_ptr<sf::Sprite> sprite;	// TODO: this isn't guaranteed initialized
	sf::Vector2i position;
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
	void translate(sf::Vector2i dpos);
	void translate(int dx, int dy);
	virtual void init();
	virtual void update(sf::Event& event);
	virtual void draw(sf::RenderWindow& window);
};
