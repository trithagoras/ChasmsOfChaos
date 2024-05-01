#include "player.h"
#include "gameobject.h"
#include <iostream>
#include <algorithm>
#include "ladderc.h"
#include "world.h"

void Player::init() {

}

void Player::update(sf::Event& event) {
    auto collisions = this->gameobject.get_collisions();
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
            // todo: put this in another function
            auto it = std::find_if(collisions.begin(), collisions.end(), [](GameObject* obj) {
                auto c = obj->get_component<LadderC>();
                return c != nullptr && c->isDown;
            });

            if (it != collisions.end()) {
                std::cout << "Going down the ladder!" << std::endl;
                World::get_instance().descend();
            } else {
                std::cout << "There's no ladder here!" << std::endl;
            }
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