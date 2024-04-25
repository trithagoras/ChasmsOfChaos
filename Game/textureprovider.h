#include <SFML/Graphics.hpp>
#include <string>
#include <optional>

class TextureProvider {
private:
	std::map<std::string, std::unique_ptr<sf::Texture>> textures;
	TextureProvider() {}
	TextureProvider(const TextureProvider&) = delete;
	TextureProvider& operator=(const TextureProvider&) = delete;
public:
	static TextureProvider& get_instance();
	sf::Texture& load_texture(const std::string& name);
	const sf::Texture& get_texture(const std::string& name);
};