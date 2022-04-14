#pragma once
#ifndef MUSICPLAYER_H
#include "SFML.h"
#include <memory>
  


class MusicPlayer
{
private:
	static sf::Music music;
	static sf::SoundBuffer soundBuffer;
	static sf::Sound sound;


public:
	MusicPlayer(const MusicPlayer&) = delete;
	MusicPlayer(MusicPlayer&&) = delete;
	MusicPlayer& operator=(const MusicPlayer&) = delete;
	MusicPlayer& operator=(MusicPlayer&&) = delete;
	

	
	static void PlayBackgroundMusic();
	static void PauseBackgroundMusic();
	static void StopBackgroundMusic();
	static void PlayHurtSound();
	static void PlayPewSound();
	static void PlaySelectSound();

private:

};

#endif // !MUSICPLAYER_H


