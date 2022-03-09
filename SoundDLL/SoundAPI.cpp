#include "SoundAPI.h"
//Calling the SDL
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include <SDL.h>
#include <iostream>
#include <vector>
#include <SDL_mixer.h>
#include "SoundInterface.h"

CSoundInterface* pManager = NULL;

namespace SoundAPI
{
	ISoundAPI* GetSoundInterface()
	{
		if (pManager == NULL)
		{
			pManager = new CSoundInterface;
		}

		return (ISoundAPI*)pManager;
	}

}