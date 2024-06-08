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
#include "inputmanager.h"

void init(World& world, sf::RenderWindow& window);
void draw(World& world, sf::RenderWindow& window);

int main() {
    sf::RenderWindow window(sf::VideoMode(960, 720), "Legends of Kordonis I: Into the Chasms of Chaos");
    window.setFramerateLimit(30);
    window.setView(sf::View(sf::FloatRect(0, 0, 320, 240)));
    window.setKeyRepeatEnabled(false);
    auto debugFullScreen = false;
    auto& ui = UI::get_instance();
    ui.initialize(window);

    // play music
    auto& soundplayer = SoundPlayer::get_instance();
    soundplayer.play_music("song-2.ogg", true);

    // set up wiggly graphics
    sf::Clock wiggleclock{};

    auto& input = InputManager::get_instance();

    World& world = World::get_instance();
    init(world, window);

    while (window.isOpen()) {
        input.keyrepeattimer = false;
        input.keyrepeatframes++;
        if (input.keyrepeatframes == input.keyrepeatmaxframes) {
            input.keyrepeatframes = 0;
            input.keyrepeattimer = true;
        }
        world.wigglejustchanged = false;
        sf::Event event;
        input.set_prev_keys();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                input.set_mod(event.key.shift);
                input.press_key(event.key.code);
                //world.update();
            } else if (event.type == sf::Event::KeyReleased) {
                input.set_mod(event.key.shift);
                input.release_key(event.key.code);
                //world.update();
            }
        }
        // wiggle
        if (wiggleclock.getElapsedTime().asSeconds() >= 0.5) {
            world.wigglestate ^= 1;
            world.wigglejustchanged = true;
            wiggleclock.restart();
        }

        // debug keys
        if (input.key_just_pressed(sf::Keyboard::R)) {
            world.reset();
            world.init();
            continue;
        } else if (input.key_just_pressed(sf::Keyboard::F)) {
            debugFullScreen = !debugFullScreen;
            if (debugFullScreen) {
                window.setView(window.getDefaultView());
            } else {
                window.setView(sf::View(sf::FloatRect(0, 0, 320, 240)));
            }
        }

        world.update();
        draw(world, window);
    }
    return 0;
}

void init(World& world, sf::RenderWindow& window) {
    ContentProvider::get_instance().load_all_content();
    GameRoomProvider::get_instance().load_all_rooms();
    world.init();
}

void draw(World& world, sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    world.draw(window);
    window.display();
}
