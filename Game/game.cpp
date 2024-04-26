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
    World world{};
    init(world, window);

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

void init(World& world, sf::RenderWindow& window) {
    auto& cp = ContentProvider::get_instance();
    cp.load_textures();
    cp.load_sprites();     // ensure you load all textures BEFORE loading sprites
    auto player = GameObjectFactory::get_instance().create_player();
    player->set_position(32, 32);

    sf::View view(sf::FloatRect((sf::Vector2f)player->get_position(), sf::Vector2f(320, 240)));
    window.setView(view);

    world.init();
    world.get_current_floor().spawn_object(std::move(player), sf::Vector2i(11, 9));
}

void update(World& world, sf::Event& event) {
    world.update(event);
}

void draw(World& world, sf::RenderWindow& window) {
    window.clear(DARKMAROON);
    world.draw(window);
    window.display();
}
