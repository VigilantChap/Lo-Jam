#include "MusicPlayer.h"


sf::Music MusicPlayer::music;
sf::SoundBuffer MusicPlayer::soundBuffer;
sf::Sound MusicPlayer::sound;


void MusicPlayer::PlayBackgroundMusic()
{
	if (!music.openFromFile("Assets/the_field_of_dreams.ogg"))
		printf("Failed to Load Music\r\n");

	else music.play();
}

void MusicPlayer::PauseBackgroundMusic() {
	music.pause();
}

void MusicPlayer::StopBackgroundMusic() {
	music.stop();
}

void MusicPlayer::PlayHurtSound()
{
	if (!soundBuffer.loadFromFile("Assets/Hit_Hurt.wav"))
		printf("Failed to Load Sound\r\n");
	
	sound.setBuffer(soundBuffer);
	sound.play();
}
void MusicPlayer::PlayPewSound()
{
	if (!soundBuffer.loadFromFile("Assets/Laser_Shoot.wav"))
		printf("Failed to Load Sound\r\n");

	sound.setBuffer(soundBuffer);
	sound.play();
}

void MusicPlayer::PlaySelectSound()
{
	if (!soundBuffer.loadFromFile("Assets/Blip_Select.wav"))
		printf("Failed to Load Sound\r\n");

	sound.setBuffer(soundBuffer);
	sound.play();
}


	
