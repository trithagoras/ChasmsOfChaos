#include "playerc.h"
#include "gameobject.h"
#include <iostream>
#include <algorithm>
#include "ladderc.h"
#include "world.h"
#include "inputmanager.h"

void PlayerC::init() {

}

void PlayerC::try_use_ladder(bool isDown) {
    auto collisions = this->gameobject.get_collisions();
    auto it = std::find_if(collisions.begin(), collisions.end(), [isDown](GameObject* obj) {
                auto c = obj->get_component<LadderC>();
                return c != nullptr && c->isDown == isDown;
            });

    const std::string dString = isDown ? "down" : "up";

    if (it != collisions.end()) {
        std::cout << "Going " << dString << " the ladder!" << std::endl;
        isDown ? World::get_instance().descend() : World::get_instance().ascend();
    } else {
        std::cout << "There's no ladder here!" << std::endl;
    }
}

void PlayerC::update() {
    auto& input = InputManager::get_instance();
    auto& world = World::get_instance();
    auto dx = 0;
    auto dy = 0;
    if (input.key_just_pressed(sf::Keyboard::Up)) {
        dy--;
    } else if (input.key_just_pressed(sf::Keyboard::Down)) {
        dy++;
    } else if (input.key_just_pressed(sf::Keyboard::Right)) {
        dx++;
    } else if (input.key_just_pressed(sf::Keyboard::Left)) {
        dx--;
    } else if (input.key_just_pressed(sf::Keyboard::Period) && input.mod_down()) {
        try_use_ladder(true);
    } else if (input.key_just_pressed(sf::Keyboard::Comma) && input.mod_down()) {
        try_use_ladder(false);
    }
    this->gameobject.translate(dx, dy);
}

void PlayerC::draw(sf::RenderWindow& window) {
    sf::View view = window.getView();
    auto [x, y] = this->gameobject.get_position();
    view.setCenter(x * 16, y * 16);
    window.setView(view);
}