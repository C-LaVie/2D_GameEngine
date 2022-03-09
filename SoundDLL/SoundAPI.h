#ifndef _SOUND_API_H_
#define _SOUND_API_H_
#include <iostream>


#ifdef SOUNDDLL_EXPORTS
#define SOUNDDLL_API __declspec(dllexport) 
#else
#define SOUNDDLL_API __declspec(dllimport) 
#endif


#ifdef SOUNDDLL_EXPORTS
#define _FUNCDLL_ extern "C" __declspec(dllexport) 
#else
#define _FUNCDLL_ extern "C" __declspec(dllimport) 
#endif


namespace SoundAPI
{

	//Pure virtual interface class
	class ISoundAPI
	{
		public:
			virtual long InitSound() = 0;
			virtual long RegisterMusic(unsigned long& MusicId, char* MusicName) = 0;
			virtual long RegisterSoundFX(unsigned long& SoundFXId, char* SoundFXName) = 0;
			//
			virtual void PlayMusic(unsigned long MusicId,int loop) = 0;
			virtual void StopMusic() = 0;
			virtual void PlaySoundFX(unsigned long SoundFXId) = 0;
	};

	//Interface function shall be load from host to get the IGraphic API pointer
	typedef ISoundAPI* (*GETSOUNDINTERFACE)();
	#define GETSOUNDINTER_NAME "GetSoundInterface"
	_FUNCDLL_ ISoundAPI* GetSoundInterface();
}



#endif //_GRAPHIC_API_H_