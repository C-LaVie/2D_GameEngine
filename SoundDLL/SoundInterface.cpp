#include "SoundInterface.h"
#include "SoundManager.h"

CSoundManager* pManager = NULL;

CSoundInterface::CSoundInterface()
{
	if (pManager == NULL)
	{
		pManager = new CSoundManager;
	}
}

CSoundInterface::~CSoundInterface()
{

}

long CSoundInterface::InitSound()
{
	if (!pManager)
	{
		pManager = new CSoundManager;
	}

	if (pManager)
	{
		return pManager->SDL_InitSound();
	}

	return -1;
}


long CSoundInterface::RegisterMusic(unsigned long& MusicId, char* MusicName)
{
	if (pManager)
	{
		return pManager->SDL_RegisterMusic(MusicId,MusicName);
	}

	return -1;
}

long CSoundInterface::RegisterSoundFX(unsigned long& SoundFXId, char* SoundFXName)
{
	if (pManager)
	{
		return pManager->SDL_RegisterSoundFX(SoundFXId,SoundFXName);
	}

	return -1;
}

//
void CSoundInterface::PlayMusic(unsigned long MusicId, int loop)
{
	if (pManager)
	{
		pManager->SDL_PlayMusic(MusicId,loop);
	}
}

void CSoundInterface::StopMusic()
{
	if (pManager)
	{
		pManager->SDL_StopMusic();
	}
}

void CSoundInterface::PlaySoundFX(unsigned long SoundFXId)
{
	if (pManager)
	{
		pManager->SDL_PlaySoundFX(SoundFXId);
	}
}
