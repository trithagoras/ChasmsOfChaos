#include "inputmanager.h"

InputManager::InputManager() {
	for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
		keysdown[static_cast<sf::Keyboard::Key>(i)] = false;
		prevkeysdown[static_cast<sf::Keyboard::Key>(i)] = false;
	}
}

InputManager& InputManager::get_instance() {
	static auto instance = InputManager();
	return instance;
}

bool InputManager::key_down(sf::Keyboard::Key key) const {
	return keysdown.at(key);
}
bool InputManager::key_just_pressed(sf::Keyboard::Key key) const {
	return keysdown.at(key) && !prevkeysdown.at(key);
}
bool InputManager::key_just_released(sf::Keyboard::Key key) const {
	return !keysdown.at(key) && prevkeysdown.at(key);
}

bool InputManager::mod_down() const {
	return moddown;
}

void InputManager::press_key(sf::Keyboard::Key key) {
	keysdown[key] = true;
}

void InputManager::release_key(sf::Keyboard::Key key) {
	keysdown[key] = false;
}

void InputManager::set_mod(bool mod) {
	moddown = mod;
}

void InputManager::set_prev_keys() {
	prevkeysdown = keysdown;
}