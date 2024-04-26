#include "player.h"

void Player::init() {

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
        }
    }
    this->translate(dx, dy);
}