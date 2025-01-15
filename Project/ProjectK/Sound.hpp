#ifndef SOUND_HPP
#define SOUND_HPP

#include "Common.hpp"

#define SOUND_CANAL_NUMBER 127
#define VOLUME_DEFAULT 50.f

enum SoundType
{
	BUTTONCLICK,
	BUTTONHOVER,
	CASESELECTION,
	UNITATTACK,
	UNITDIE,
	GOALMARKED,
	TOTALSOUND
};

enum MusicId
{
	BACKGROUNDCALM = 1,
	BACKGROUNDCOMBAT
};

class Sound
{
private:

	float volume;

	size_t testSoundIndex = 0;

	void ApplyVolume();
public:
	sf::SoundBuffer soundBuffer[TOTALSOUND];
	sf::Sound sound[SOUND_CANAL_NUMBER];
	sf::Music music;

	Sound();
	~Sound();

	void InitSound();
	void StartBackgroundMusic(unsigned int _musicId);
	void SetVolume(float _volume);
	size_t GetTestSoundIndex() { return testSoundIndex; }
	void IncrementTestSoundIndex()
	{
		testSoundIndex++;
		if (testSoundIndex == TOTALSOUND)
		{
			testSoundIndex = 0;
		}
	}
	void UseSound(unsigned int _soundId);
};



#endif