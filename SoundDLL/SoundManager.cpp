#include "SoundManager.h"
#include <Windows.h>

#define ERROR_INIT -1

using namespace std;

CSoundManager::CSoundManager()
{
	m_bIsDebug = false;
	m_vecMusic.clear();
	m_vecSoundFX.clear();

	m_ulMusicId = 1;
	m_ulSoundFXId = 1;
	m_bIsMusicOn = GetPrivateProfileIntA("Sound", "IsMusicOn", 1, "..//Config//GameManager.ini");
	m_bIsSoundFXOn = GetPrivateProfileIntA("Sound", "IsSoundFXOn", 1, "..//Config//GameManager.ini");
}
CSoundManager::~CSoundManager()
{
	m_bIsDebug = false;
	m_vecMusic.clear();
	m_vecSoundFX.clear();

	Mix_CloseAudio();
	Mix_Quit();
}

long CSoundManager::SDL_InitSound()
{
	int flags = MIX_INIT_MP3;
	int initted = Mix_Init(MIX_INIT_MP3 | MIX_INIT_MOD | MIX_INIT_FLAC | MIX_INIT_OGG);
	if ((initted & flags) != flags)
	{
		char LogBuff[256] = { 0 };
		sprintf_s(LogBuff, "Mix_Init: Failed to init SDL_Mixer\n");
		LOG_DEBUG(LogBuff);

		sprintf_s(LogBuff, "Mix_Init: %s\n", Mix_GetError());
		LOG_DEBUG(LogBuff);
		return ERROR_INIT;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		char LogBuff[256] = { 0 };
		sprintf_s(LogBuff, "Mix_OpenAudio: %s\n", Mix_GetError());
		LOG_DEBUG(LogBuff);
		return ERROR_INIT;
	}

	Mix_AllocateChannels(32);

}


long CSoundManager::SDL_RegisterMusic(unsigned long& MusicId, char* MusicName)
{
	Mix_Music* p = Mix_LoadMUS(MusicName);
	if (p)
	{
		m_vecMusic.push_back(make_pair(p, m_ulMusicId));
		MusicId = m_ulMusicId;
		++m_ulMusicId;
		return 0;
	}
	return -1;
}

long CSoundManager::SDL_RegisterSoundFX(unsigned long& SoundFXId, char* SoundFXName)
{
	Mix_Chunk* p = Mix_LoadWAV(SoundFXName);
	if (p)
	{
		m_vecSoundFX.push_back(make_pair(p, m_ulSoundFXId));
		SoundFXId = m_ulSoundFXId;
		++m_ulSoundFXId;
		return 0;
	}
	return -1;
}

//
void CSoundManager::SDL_PlayMusic(unsigned long MusicId, int loop)
{
	if (m_bIsMusicOn && Mix_PlayMusic(GetSDLMusic(MusicId), loop) == -1)
	{
		char TempBuf[256] = { 0 };
		sprintf_s(TempBuf, "Mix_PlayMusic error: %s\n", Mix_GetError());
		LOG_DEBUG(TempBuf);
	}
}

void CSoundManager::SDL_StopMusic()
{
	//need to do
	Mix_HaltMusic();
}

void CSoundManager::SDL_PlaySoundFX(unsigned long SoundFXId)
{
	if (m_bIsSoundFXOn) Mix_PlayChannel(-1, GetSDLChunk(SoundFXId), 0);
}


Mix_Music* CSoundManager::GetSDLMusic(unsigned long Id)
{
	Mix_Music* p = NULL;
	if (Id < m_ulMusicId)
	{
		//Seaching the SDL music pointer
		vector < pair < Mix_Music*, unsigned long> >::iterator l_itor = m_vecMusic.begin();
		for (int i = 0; i<m_ulMusicId; ++i)
		{
			if (l_itor->second == Id)
			{
				p = (Mix_Music*)(l_itor)->first;
				break;
			}
			++l_itor;
		}

	}
	return p;
}

Mix_Chunk* CSoundManager::GetSDLChunk(unsigned long Id)
{
	Mix_Chunk* p = NULL;
	if (Id < m_ulSoundFXId)
	{
		//Seaching the SDL music pointer
		vector < pair < Mix_Chunk*, unsigned long> >::iterator l_itor = m_vecSoundFX.begin();
		for (int i = 0; i<m_ulSoundFXId; ++i)
		{
			if (l_itor->second == Id)
			{
				p = (Mix_Chunk*)(l_itor)->first;
				break;
			}
			++l_itor;
		}

	}
	return p;
}