#include <iostream>
#include <SFML/Graphics.hpp>
#include "textureprovider.h"
#include "world.h"
#include <memory>
#include "player.h"
#include <libtcod.hpp>

void init(World& world) {
    auto& gameTexture = TextureProvider::getInstance().loadTexture("game-tiles1.png");
    auto playerSprite = std::make_unique<sf::Sprite>(sf::Sprite(gameTexture, sf::IntRect(28 * 16, 16, 16, 16)));
    playerSprite->setScale(2, 2);
    playerSprite->setColor(sf::Color::Yellow);
    playerSprite->setPosition(32, 32);
    auto player = std::make_unique<Player>();
    player->set_sprite(std::move(playerSprite));
    world.place_object_in_world(std::move(player), sf::Vector2i(16, 16));
    world.init();
}

void update(World& world, sf::Event& event) {
    world.update(event);
}

void draw(World& world, sf::RenderWindow& window) {
    window.clear();
    world.draw(window);
    window.display();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    window.setFramerateLimit(60);
    World world{};
    init(world);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            update(world, event);
        }
        
        draw(world, window);
    }

    return 0;
}