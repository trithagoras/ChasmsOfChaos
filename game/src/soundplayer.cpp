#include "soundplayer.h"
#include <format>

SoundPlayer& SoundPlayer::get_instance() {
	static SoundPlayer player{};
	return player;
}

void SoundPlayer::play_music(const std::string& name, bool loop) {
	stop_music();
	if (!currentMusic.openFromFile(std::format("content/sound/{}", name))) {
		return;		// music will not play
	}
	currentMusic.setLoop(loop);
	currentMusic.play();
}

void SoundPlayer::stop_music() {
	currentMusic.stop();
}