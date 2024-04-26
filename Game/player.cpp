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

void Player::draw(sf::RenderWindow& window) {
    sf::View view = window.getView();
    auto [x, y] = get_position();
    view.setCenter(x * 16, y * 16);
    window.setView(view);
    GameObject::draw(window);
}