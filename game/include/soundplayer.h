#pragma once
#include <string>
#include <SFML/Audio.hpp>
#include <vector>

class SoundPlayer {
private:
	SoundPlayer() = default;
	SoundPlayer(SoundPlayer&) = delete;
	sf::Music currentMusic;		// current music being played. TODO: make a vector and also make a new vector for sf::Sound

public:
	static SoundPlayer& get_instance();

	/// <summary>
	/// Plays a music file potentially on loop.
	/// </summary>
	/// <param name="name">Relative path to the audio file</param>
	/// <param name="loop">Whether to loop the file</param>
	void play_music(const std::string& name, bool loop = false);

	/// <summary>
	/// Stops all music.
	/// </summary>
	void stop_music();
};