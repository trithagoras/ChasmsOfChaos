#include <iostream>
#include <SFML/Graphics.hpp>
#include "textureprovider.h"
#include "world.h"
#include <memory>
#include "player.h"
#include <libtcod.hpp>
#include "gameobjectfactory.h"
#include "gamecolors.h"
#include "contentprovider.h"

void init(World& world);
void update(World& world, sf::Event& event);
void draw(World& world, sf::RenderWindow& window);

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Legends of Kordonis I: Into the Chasms of Chaos");
    window.setFramerateLimit(60);
    World world{};
    init(world);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                update(world, event);
            }
        }
        draw(world, window);
    }
    return 0;
}

void init(World& world) {
    ContentProvider::get_instance().load_sprites();
    auto& gameTexture = TextureProvider::get_instance().load_texture("game-tiles.png");
    auto player = GameObjectFactory::get_instance().create_player();
    world.spawn_in_world(std::move(player), sf::Vector2i(16, 16));
    world.init();
}

void update(World& world, sf::Event& event) {
    std::cout << "update" << std::endl;
    world.update(event);
}

void draw(World& world, sf::RenderWindow& window) {
    window.clear(DARKMAROON);
    world.draw(window);
    window.display();
}
