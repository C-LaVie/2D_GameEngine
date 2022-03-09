#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include <SDL.h>
#include <iostream>
#include <vector>

#include "InputAPI.h"
#include "EventQueue.h"

class CInputManager
{
	public:
		CInputManager();
		~CInputManager();
		void SDL_GetInput(stPlayerInput& Input);
		void SDL_SetOnAutoEventInter(PlayerInputAPI::IPlayerInputOnAutoEvent*p);
		void ReloadKeyAssignment();

		//Thread
		void ThreadEventHandling();

	private:

		PlayerInputAPI::IPlayerInputOnAutoEvent* m_pAutoEvent;
//		HANDLE m_hThread;
		HANDLE m_hSemLock;
		SDL_Thread* mThread;
		CEventQueue m_queue;

		stPlayerInput m_PlayerInput;

		bool m_bIsDebug;
		//Key mapping from the player
		long KeyLeft;
		long KeyRight;
		long KeyUp;
		long KeyDown;
		long KeyEnter;
		long KeyErase;
		long KeyPause;
		//Special key to map any kind of action you wishes, like hit, fire, menu, etc...
		long Keycontrol_Key_0;
		long Keycontrol_Key_1;
		long Keycontrol_Key_2;
		long Keycontrol_Key_3;
		long Keycontrol_Key_4;
		long Keycontrol_Key_5;
		long Keycontrol_Key_6;
		long Keycontrol_Key_7;
		long Keycontrol_Key_8;
		long Keycontrol_Key_9;
};

#define LOG_DEBUG(a) \
	if(m_bIsDebug) std::cout << a << std::endl;
#endif //_INPUT_MANAGER_H_