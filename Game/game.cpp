#include <iostream>
#include <SFML/Graphics.hpp>
#include "textureprovider.h"
#include "world.h"
#include <memory>
#include "player.h"
#include <libtcod.hpp>
#include "gameobjectfactory.h"
#include "gamecolors.h"

void init(World& world);
void update(World& world, sf::RenderWindow& window, sf::Event& event);
void draw(World& world, sf::RenderWindow& window);

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    window.setFramerateLimit(60);
    World world{};
    init(world);
    draw(world, window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                update(world, window, event);   // only updates on key press including redraws... probably a bad idea
            }
        }
    }
    return 0;
}

void init(World& world) {
    auto& gameTexture = TextureProvider::get_instance().load_texture("game-tiles.png");
    auto player = GameObjectFactory::get_instance().create_player();
    world.spawn_in_world(std::move(player), sf::Vector2i(16, 16));
    world.init();
}

void update(World& world, sf::RenderWindow& window, sf::Event& event) {
    std::cout << "update" << std::endl;
    world.update(event);
    draw(world, window);
}

void draw(World& world, sf::RenderWindow& window) {
    window.clear(DARKMAROON);
    world.draw(window);
    window.display();
}
