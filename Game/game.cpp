#include <iostream>
#include <SFML/Graphics.hpp>
#include "world.h"
#include <memory>
#include "player.h"
#include <libtcod.hpp>
#include "gameobjectfactory.h"
#include "gamecolors.h"
#include "contentprovider.h"

void init(World& world, sf::RenderWindow& window);
void update(World& world, sf::Event& event);
void draw(World& world, sf::RenderWindow& window);

int main() {
    sf::RenderWindow window(sf::VideoMode(960, 720), "Legends of Kordonis I: Into the Chasms of Chaos");
    window.setFramerateLimit(60);
    window.setView(sf::View(sf::FloatRect(0, 0, 320, 240)));

    World world{};
    init(world, window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::R) {
                    // TODO: DEBUG CODE
                    world = World{};
                    world.init();
                    continue;
                }
                update(world, event);
            }
        }
        draw(world, window);
    }
    return 0;
}

void init(World& world, sf::RenderWindow& window) {
    auto& cp = ContentProvider::get_instance();
    cp.load_textures();
    cp.load_sprites();     // ensure you load all textures BEFORE loading sprites
    world.init();
}

void update(World& world, sf::Event& event) {
    world.update(event);
}

void draw(World& world, sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    world.draw(window);
    window.display();
}
