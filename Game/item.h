#pragma once
#include <string>
#include <SFML/Graphics/Sprite.hpp>

/// <summary>
/// This is NOT the item component. This is simply a mapping from the items.json file. See @itemc.h for the component.
/// </summary>
class Item {
public:
	std::string name;
	std::string description;
	std::string spriteName;
};