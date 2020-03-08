#pragma once
#ifndef MUSICPLAYER_H
#include "SFML.h"


class MusicPlayer
{
public:
	sf::Music music;
	sf::SoundBuffer soundBuffer;
	sf::Sound sound;

	MusicPlayer();
	~MusicPlayer();

	void PlayBackgroundMusic();
	void PlayHurtSound();
	void PlayPewSound();
	void PlaySelectSound();
};

#endif // !MUSICPLAYER_H


