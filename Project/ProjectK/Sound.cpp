#include "Sound.hpp"

//Load to memory all sound, use of .ogg for a more compressed sound than .wav
void Sound::InitSound()
{
	TOTALSOUND;
	soundBuffer[BUTTONCLICK].loadFromFile("Sound/ButtonClick.ogg");
	soundBuffer[BUTTONHOVER].loadFromFile("Sound/ButtonHover.ogg");
	soundBuffer[CASESELECTION].loadFromFile("Sound/CaseSelection.ogg");
	soundBuffer[UNITATTACK].loadFromFile("Sound/UnitAttack.ogg");
	soundBuffer[UNITDIE].loadFromFile("Sound/UnitDie.ogg");
	soundBuffer[GOALMARKED].loadFromFile("Sound/GoalMarked.ogg");

	SetVolume(VOLUME_DEFAULT);
}

//Play a sound (enum with all sound id in sound.hpp)
void Sound::UseSound(unsigned int _soundId)
{
	size_t i = 0;
	//Pas le droit d'utiliser des breaks dans un while d'après les règles de codage mais tkt, je l'ai ai changer par des returns
	while (true)
	{
		if (i == SOUND_CANAL_NUMBER)
		{
			std::cout << "Can't play sound. No sound canal left !" << std::endl;
			return;
		}
		if (sound[i].getStatus() == sf::Sound::Stopped)
		{
			sound[i].setBuffer(soundBuffer[_soundId]);
			sound[i].play();
			return;
		}
		i++;
	}
}

//Start the background music and make it loop
void Sound::StartBackgroundMusic(unsigned int _musicId)
{
	music.stop();
	switch (_musicId)
	{
	case BACKGROUNDCALM:
		music.openFromFile("Sound/IndustrialMetal(Calm Loop)-MomotMusic.ogg");
		music.play();
		break;
	case BACKGROUNDCOMBAT:
		music.openFromFile("Sound/IndustrialMetal(Combat Loop)-MomotMusic.ogg");
		music.play();
		break;
	default:
		music.stop();
		break;
	}
	music.setLoop(true);
}


//Set the volume, the value should range between 0(min) and 100(max)
void Sound::SetVolume(float _volume)
{
	if (_volume > 100)
	{
		_volume = 100;
	}
	if (_volume < 0)
	{
		_volume = 0;
	}
	volume = _volume;
	ApplyVolume();
}

//Apply the volume to all sound chanel
void Sound::ApplyVolume()
{
	for (size_t i = 0; i < SOUND_CANAL_NUMBER; i++)
	{
		sound[i].setVolume(volume);
	}
	music.setVolume(volume);
}

Sound::Sound()
{
	InitSound();
}

Sound::~Sound()
{

}