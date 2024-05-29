#pragma once
#include <SFML/System.hpp>
#include <string>
#include <libtcod.hpp>
#include <iterator>

static sf::Uint32 str_to_hex(const std::string& s) {
    return std::stoul(s, 0, 16);
}

template <typename T>
static T random_choose_vec(std::vector<T> vec) {
    auto rng = TCODRandom::getInstance();
    return vec[rng->getInt(0, vec.size)];
}

template<typename K, typename V>
K random_choose_map_key(const std::map<K, V>& map) {
    if (map.empty()) {
        throw std::runtime_error("Cannot select from an empty map");
    }

    auto rng = TCODRandom::getInstance();
    auto idx = rng->getInt(0, map.size() - 1);
    auto it = map.begin();
    std::advance(it, idx);
    return it->first;
}