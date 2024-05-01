#include "player.h"
#include "gameobject.h"
#include <iostream>
#include <algorithm>
#include "ladderc.h"
#include "world.h"

void Player::init() {

}

void Player::try_use_ladder(bool isDown) {
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

void Player::update(sf::Event& event) {
    auto dx = 0;
    auto dy = 0;
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Up:
                dy = -1;
                break;
            case sf::Keyboard::Left:
                dx = -1;
                break;
            case sf::Keyboard::Down:
                dy = 1;
                break;
            case sf::Keyboard::Right:
                dx = 1;
                break;
            case sf::Keyboard::Period:
                try_use_ladder(true);
                break;
            case sf::Keyboard::Comma:
                try_use_ladder(false);
                break;
            default:
                break;
        }
    }
    this->gameobject.translate(dx, dy);

    // checking collisions with other gameobjects
    //auto collisions = this->gameobject.get_collisions();
    //for (auto obj : collisions) {
    //    std::cout << "Player has collided with " << obj->get_name() << std::endl;
    //}
}

void Player::draw(sf::RenderWindow& window) {
    sf::View view = window.getView();
    auto [x, y] = this->gameobject.get_position();
    view.setCenter(x * 16, y * 16);
    window.setView(view);
}