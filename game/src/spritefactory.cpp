#include "spritefactory.h"
#include "contentprovider.h"

SpriteFactory& SpriteFactory::get_instance() {
	static SpriteFactory factory{};
	return factory;
}

SpriteWrapper SpriteFactory::create_sprite(const std::string& name) const {
	auto& sprite = ContentProvider::get_instance().get_sprite(name);
	return SpriteWrapper(sprite);	// copy
}