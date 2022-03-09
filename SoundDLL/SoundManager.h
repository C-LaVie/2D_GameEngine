#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>

#include "SoundAPI.h"

class CSoundManager
{
	public:
		CSoundManager();
		~CSoundManager();

		long SDL_InitSound();
		long SDL_RegisterMusic(unsigned long& MusicId, char* MusicName);
		long SDL_RegisterSoundFX(unsigned long& SoundFXId, char* SoundFXName);
		//
		void SDL_PlayMusic(unsigned long MusicId, int loop);
		void SDL_StopMusic();
		void SDL_PlaySoundFX(unsigned long SoundFXId);

	private:
		bool m_bIsDebug;
		//List of music and SoundFX register in the sound module
		unsigned long m_ulMusicId;
		std::vector < std::pair <Mix_Music*, unsigned long> > m_vecMusic;

		unsigned long m_ulSoundFXId;
		std::vector < std::pair <Mix_Chunk*, unsigned long> > m_vecSoundFX;

		Mix_Music* GetSDLMusic(unsigned long Id);
		Mix_Chunk* GetSDLChunk(unsigned long Id);

		bool m_bIsMusicOn;
		bool m_bIsSoundFXOn;
};

#define LOG_DEBUG(a) \
	if(m_bIsDebug) std::cout << a << std::endl;

#endif //_SOUND_MANAGER_H_