#include "MusicPlayer.h"

std::unique_ptr<MusicPlayer> MusicPlayer::musicPlayerInstance = nullptr;

MusicPlayer::MusicPlayer()
{
}


MusicPlayer::~MusicPlayer()
{
}

MusicPlayer * MusicPlayer::GetInstance()
{
	if (musicPlayerInstance.get() == nullptr)
	{
		musicPlayerInstance.reset(new MusicPlayer);
	}
	return musicPlayerInstance.get();
}

void MusicPlayer::PlayBackgroundMusic()
{
	if (!music.openFromFile("Assets/the_field_of_dreams.mp3"))
		printf("Failed to Load Music\r\n");
	music.play();
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


	
