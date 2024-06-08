#pragma once
#include <string>
#include <memory>
#include "spritewrapper.h"

class SpriteFactory {
	SpriteFactory() {}
	SpriteFactory(const SpriteFactory&) = delete;
	SpriteFactory& operator=(const SpriteFactory&) = delete;

public:
	static SpriteFactory& get_instance();
	SpriteWrapper create_sprite(const std::string& name) const;
};