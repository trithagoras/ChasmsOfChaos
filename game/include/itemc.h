#pragma once
#include <memory>
#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include "component.h"
#include "item.h"

class ItemC : public Component {
    std::unique_ptr<Item> item;

public:
    ItemC(GameObject& gameobject) : Component(gameobject) {}
    void init() override {}
    void update() override {}
    void draw(sf::RenderWindow& window) override {}

    const Item& get_item() const {
        return *item;
    }
    void set_item(std::unique_ptr<Item> item) {
        this->item = std::move(item);
    }
};