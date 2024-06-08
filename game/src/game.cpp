#include <iostream>
#include <SFML/Graphics.hpp>
#include "world.h"
#include <memory>
#include "playerc.h"
#include <libtcod.hpp>
#include "gameobjectfactory.h"
#include "gamecolors.h"
#include "contentprovider.h"
#include "rooms.h"
#include "ui.h"
#include "soundplayer.h"

void init(World& world, sf::RenderWindow& window);
void update(World& world, sf::Event& event);
void draw(World& world, sf::RenderWindow& window);

int main() {
    sf::RenderWindow window(sf::VideoMode(960, 720), "Legends of Kordonis I: Into the Chasms of Chaos");
    window.setFramerateLimit(60);
    window.setView(sf::View(sf::FloatRect(0, 0, 320, 240)));
    auto debugFullScreen = false;
    auto& ui = UI::get_instance();
    ui.initialize(window);

    // play music
    auto& soundplayer = SoundPlayer::get_instance();
    soundplayer.play_music("song-2.ogg", true);

    // set up wiggly graphics
    sf::Clock wiggleclock{};

    World& world = World::get_instance();
    init(world, window);

    while (window.isOpen()) {
        world.wigglejustchanged = false;
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                // TODO: DEBUG CODE
                // =======================================================
                if (event.key.code == sf::Keyboard::R) {
                    world.reset();
                    world.init();
                    continue;
                }
                else if (event.key.code == sf::Keyboard::F) {
                    debugFullScreen = !debugFullScreen;
                    if (debugFullScreen) {
                        window.setView(window.getDefaultView());
                    } else {
                        window.setView(sf::View(sf::FloatRect(0, 0, 320, 240)));
                    }
                    continue;
                }
                // =======================================================
                update(world, event);
            }
        }
        // wiggle
        if (wiggleclock.getElapsedTime().asSeconds() >= 0.5) {
            world.wigglestate ^= 1;
            world.wigglejustchanged = true;
            wiggleclock.restart();
        }

        draw(world, window);
    }
    return 0;
}

void init(World& world, sf::RenderWindow& window) {
    ContentProvider::get_instance().load_all_content();
    GameRoomProvider::get_instance().load_all_rooms();
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
