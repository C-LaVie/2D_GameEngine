#ifndef _SOUND_INTERFACE_H_
#define _SOUND_INTERFACE_H_

#include "SoundAPI.h"
using namespace SoundAPI;
class CSoundInterface :public ISoundAPI
{
	public:
		CSoundInterface();
		~CSoundInterface();

		virtual long InitSound();
		virtual long RegisterMusic(unsigned long& MusicId, char* MusicName) ;
		virtual long RegisterSoundFX(unsigned long& SoundFXId, char* SoundFXName) ;
		//
		virtual void PlayMusic(unsigned long MusicId, int loop) ;
		virtual void StopMusic() ;
		virtual void PlaySoundFX(unsigned long SoundFXId) ;
	
};

#endif //_SOUND_INTERFACE_H_