#pragma once
#include <SFML/System.hpp>
#include <string>

static sf::Uint32 str_to_hex(const std::string& s) {
    return std::stoul(s, 0, 16);
}