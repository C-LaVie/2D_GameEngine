#include "InputAPI.h"

#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include <SDL.h>
#include <iostream>
#include <vector>

#include "InputInterface.h"

CInputInterface* pManager = NULL;

namespace PlayerInputAPI
{
	IPlayerInputAPI* GetInputInterface()
	{
		if (pManager == NULL)
		{
			pManager = new CInputInterface;
		}

		return (IPlayerInputAPI*)pManager;
	}

}