#pragma once
#include <SFML/Window.hpp>
#include <map>

class InputManager {
private:
	InputManager();
	InputManager(InputManager&) = delete;

	std::map<sf::Keyboard::Key, bool> keysdown;
	std::map<sf::Keyboard::Key, bool> prevkeysdown;

	// only shift modifer for now
	bool moddown = false;

public:
	// TODO: better system for this shit...
	int keyrepeatframes = 0;
	int keyrepeatmaxframes = 5;	// key repeats every 15 frames
	bool keyrepeattimer = false;	// true once keyrepeatframes == keyrepeatmaxframes

	static InputManager& get_instance();
	bool key_down(sf::Keyboard::Key) const;
	bool key_just_pressed(sf::Keyboard::Key) const;
	bool key_just_released(sf::Keyboard::Key) const;
	bool mod_down() const;

	/// <summary>
	/// DO NOT USE. This is used at game.cpp
	/// </summary>
	/// <param name=""></param>
	void press_key(sf::Keyboard::Key);
	/// <summary>
	/// DO NOT USE. This is used at game.cpp
	/// </summary>
	/// <param name=""></param>
	void release_key(sf::Keyboard::Key);
	/// <summary>
	/// DO NOT USE. This is used at game.cpp
	/// </summary>
	/// <param name=""></param>
	void set_prev_keys();

	/// <summary>
	/// DO NOT USE. This is used at game.cpp
	/// </summary>
	void set_mod(bool);
};