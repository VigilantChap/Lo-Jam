#pragma once
#ifndef MUSICPLAYER_H
#include "SFML.h"
#include <memory>


class MusicPlayer
{
private:
	sf::Music music;
	sf::SoundBuffer soundBuffer;
	sf::Sound sound;


public:
	MusicPlayer(const MusicPlayer&) = delete;
	MusicPlayer(MusicPlayer&&) = delete;
	MusicPlayer& operator=(const MusicPlayer&) = delete;
	MusicPlayer& operator=(MusicPlayer&&) = delete;
	
	static MusicPlayer * GetInstance();
	
	void PlayBackgroundMusic();
	void PlayHurtSound();
	void PlayPewSound();
	void PlaySelectSound();
private:
	MusicPlayer();
	~MusicPlayer();

	static std::unique_ptr<MusicPlayer> musicPlayerInstance;
	friend std::default_delete<MusicPlayer>;
};

#endif // !MUSICPLAYER_H


