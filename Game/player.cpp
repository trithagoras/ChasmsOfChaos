#include "player.h"

void Player::init() {

}

void Player::update(sf::Event& event) {
    auto dx = 0;
    auto dy = 0;
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::W:
            dy = -16;
            break;
        case sf::Keyboard::A:
            dx = -16;
            break;
        case sf::Keyboard::S:
            dy = 16;
            break;
        case sf::Keyboard::D:
            dx = 16;
            break;
        }
    }
    this->translate(dx, dy);
}