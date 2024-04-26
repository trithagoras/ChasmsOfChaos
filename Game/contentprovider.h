#pragma once
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ContentProvider {
	ContentProvider() {}
	ContentProvider(const ContentProvider&) = delete;
	ContentProvider& operator=(const ContentProvider&) = delete;

	std::map<std::string, std::unique_ptr<json>> sprites;

public:
	static ContentProvider& get_instance();
	void load_sprites();
	const json& get_sprite(const std::string& name);
};