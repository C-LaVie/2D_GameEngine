#include"InputManager.h"
using namespace PlayerInputAPI;

/*DWORD WINAPI*/static int EventHandling(void* Param)
{
	CInputManager* m_pInput = (CInputManager*)Param;
	m_pInput->ThreadEventHandling();

	return 0;
}


CInputManager::CInputManager()
{
	m_bIsDebug = false;

	m_pAutoEvent = NULL;

	memset(&m_PlayerInput, 0, sizeof(m_PlayerInput));

	//Shemaphore access control
	m_hSemLock = CreateSemaphore(NULL, 1, 1, NULL);

	//Start the thread for the key detection
//	DWORD dwThreadID;
//	m_hThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)EventHandling, this, 0, &dwThreadID);
	mThread = SDL_CreateThread(EventHandling, "EventHandling", (void *)this);

	ReloadKeyAssignment();
}

CInputManager::~CInputManager()
{
	m_pAutoEvent = NULL;
}


void CInputManager :: ReloadKeyAssignment()
{
	//Load the key mapping
	Keycontrol_Key_0 = GetPrivateProfileIntA("PlayerKey", "Keycontrol_Key_0", SDLK_y, "..//Config//GameManager.ini");
	Keycontrol_Key_1 = GetPrivateProfileIntA("PlayerKey", "Keycontrol_Key_1", SDLK_u, "..//Config//GameManager.ini");
	Keycontrol_Key_2 = GetPrivateProfileIntA("PlayerKey", "Keycontrol_Key_2", SDLK_i, "..//Config//GameManager.ini");
	Keycontrol_Key_3 = GetPrivateProfileIntA("PlayerKey", "Keycontrol_Key_3", SDLK_o, "..//Config//GameManager.ini");
	Keycontrol_Key_4 = GetPrivateProfileIntA("PlayerKey", "Keycontrol_Key_4", SDLK_p, "..//Config//GameManager.ini");
	Keycontrol_Key_5 = GetPrivateProfileIntA("PlayerKey", "Keycontrol_Key_5", SDLK_h, "..//Config//GameManager.ini");
	Keycontrol_Key_6 = GetPrivateProfileIntA("PlayerKey", "Keycontrol_Key_6", SDLK_j, "..//Config//GameManager.ini");
	Keycontrol_Key_7 = GetPrivateProfileIntA("PlayerKey", "Keycontrol_Key_7", SDLK_k, "..//Config//GameManager.ini");
	Keycontrol_Key_8 = GetPrivateProfileIntA("PlayerKey", "Keycontrol_Key_8", SDLK_l, "..//Config//GameManager.ini");
	Keycontrol_Key_9 = GetPrivateProfileIntA("PlayerKey", "Keycontrol_Key_9", SDLK_m, "..//Config//GameManager.ini");

	KeyUp = GetPrivateProfileIntA("PlayerKey", "KeyUp", SDLK_w, "..//Config//GameManager.ini");
	KeyDown = GetPrivateProfileIntA("PlayerKey", "KeyDown", SDLK_s, "..//Config//GameManager.ini");
	KeyLeft = GetPrivateProfileIntA("PlayerKey", "KeyLeft", SDLK_a, "..//Config//GameManager.ini");
	KeyRight = GetPrivateProfileIntA("PlayerKey", "KeyRight", SDLK_d, "..//Config//GameManager.ini");


	KeyEnter = GetPrivateProfileIntA("PlayerKey", "KeyEnter", SDLK_KP_ENTER, "..//Config//GameManager.ini");
	KeyErase = GetPrivateProfileIntA("PlayerKey", "KeyErase", SDLK_r, "..//Config//GameManager.ini");
}

void CInputManager::SDL_GetInput(stPlayerInput& Input)
{
	//Lock the key control access


	
	//Unlock

	//Update input queue
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		m_queue.Push(event);
	}

	WaitForSingleObject(m_hSemLock, INFINITE);
	memcpy(&Input, &m_PlayerInput, sizeof(stPlayerInput));
	ReleaseSemaphore(m_hSemLock, 1, NULL);
}

void CInputManager::SDL_SetOnAutoEventInter(IPlayerInputOnAutoEvent*p)
{
	m_pAutoEvent = p;
}


void CInputManager::ThreadEventHandling()
{
	//Never stop
	//SDL_InitSubSystem(SDL_INIT_EVERYTHING);
	//SDL_Init();


	while (true)
	{
		//Lock the input access
	//	
		//Do the input check
		SDL_Event event;
		m_queue.Pop(event);
		
		WaitForSingleObject(m_hSemLock, INFINITE);
		//Polling the event 
		
	//	while (SDL_PollEvent(&event))
	//	{
			switch (event.type)
			{

			case SDL_QUIT:
			{
				exit(0);
			}

			break;
			case SDL_MOUSEMOTION:
			{
				m_PlayerInput.Mouse_X = event.motion.x;
				m_PlayerInput.Mouse_Y = event.motion.y;
			}
			break;

			case SDL_MOUSEBUTTONDOWN:
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					m_PlayerInput.Mouse_Click = 1;
				}
			}
			break;

			case SDL_KEYDOWN:
			{
				//Move
				if (KeyLeft == event.key.keysym.sym)
				{
					m_PlayerInput.Left = 1;
				}
				else if (KeyRight == event.key.keysym.sym)
				{
					m_PlayerInput.Right = 1;
				}
				else if (KeyUp == event.key.keysym.sym)
				{
					m_PlayerInput.Up = 1;
				}
				else if (KeyDown == event.key.keysym.sym)
				{
					m_PlayerInput.Down = 1;
				}
				//control key - 0 to 9
				else if (Keycontrol_Key_0 == event.key.keysym.sym)
				{
					m_PlayerInput.control_Key_0 = 1;
				}
				else if (Keycontrol_Key_1 == event.key.keysym.sym)
				{
					m_PlayerInput.control_Key_1 = 1;
				}
				else if (Keycontrol_Key_2 == event.key.keysym.sym)
				{
					m_PlayerInput.control_Key_2 = 1;
				}
				else if (Keycontrol_Key_3 == event.key.keysym.sym)
				{
					m_PlayerInput.control_Key_3 = 1;
				}
				else if (Keycontrol_Key_4 == event.key.keysym.sym)
				{
					m_PlayerInput.control_Key_4 = 1;
				}
				else if (Keycontrol_Key_5 == event.key.keysym.sym)
				{
					m_PlayerInput.control_Key_5 = 1;
				}
				else if (Keycontrol_Key_6 == event.key.keysym.sym)
				{
					m_PlayerInput.control_Key_6 = 1;
				}
				else if (Keycontrol_Key_7 == event.key.keysym.sym)
				{
					m_PlayerInput.control_Key_7 = 1;
				}
				else if (Keycontrol_Key_8 == event.key.keysym.sym)
				{
					m_PlayerInput.control_Key_8 = 1;
				}
				else if (Keycontrol_Key_9 == event.key.keysym.sym)
				{
					m_PlayerInput.control_Key_9 = 1;
				}

				//Special key
				else if (KeyEnter == event.key.keysym.sym)
				{
					m_PlayerInput.Enter = 1;
				}
				else if (KeyErase == event.key.keysym.sym)
				{
					m_PlayerInput.Erase = 1;
				}
				else if (KeyPause == event.key.keysym.sym)
				{
					m_PlayerInput.Pause = 1;
				}
			}
			break;

			case SDL_KEYUP:
			{
				//Move
				if (KeyLeft == event.key.keysym.sym)
				{
					m_PlayerInput.Left = 0;
				}
				else if (KeyRight == event.key.keysym.sym)
				{
					m_PlayerInput.Right = 0;
				}
				else if (KeyUp == event.key.keysym.sym)
				{
					m_PlayerInput.Up = 0;
				}
				else if (KeyDown == event.key.keysym.sym)
				{
					m_PlayerInput.Down = 0;
				}
				//control key - 0 to 9
				else if (Keycontrol_Key_0 == event.key.keysym.sym)
				{
					m_PlayerInput.control_Key_0 = 0;
				}
				else if (Keycontrol_Key_1 == event.key.keysym.sym)
				{
					m_PlayerInput.control_Key_1 = 0;
				}
				else if (Keycontrol_Key_2 == event.key.keysym.sym)
				{
					m_PlayerInput.control_Key_2 = 0;
				}
				else if (Keycontrol_Key_3 == event.key.keysym.sym)
				{
					m_PlayerInput.control_Key_3 = 0;
				}
				else if (Keycontrol_Key_4 == event.key.keysym.sym)
				{
					m_PlayerInput.control_Key_4 = 0;
				}
				else if (Keycontrol_Key_5 == event.key.keysym.sym)
				{
					m_PlayerInput.control_Key_5 = 0;
				}
				else if (Keycontrol_Key_6 == event.key.keysym.sym)
				{
					m_PlayerInput.control_Key_6 = 0;
				}
				else if (Keycontrol_Key_7 == event.key.keysym.sym)
				{
					m_PlayerInput.control_Key_7 = 0;
				}
				else if (Keycontrol_Key_8 == event.key.keysym.sym)
				{
					m_PlayerInput.control_Key_8 = 0;
				}
				else if (Keycontrol_Key_9 == event.key.keysym.sym)
				{
					m_PlayerInput.control_Key_9 = 0;
				}
				//Special key
				else if (KeyEnter == event.key.keysym.sym)
				{
					m_PlayerInput.Enter = 0;
				}
				else if (KeyErase == event.key.keysym.sym)
				{
					m_PlayerInput.Erase = 0;
				}
				else if (KeyPause == event.key.keysym.sym)
				{
					m_PlayerInput.Pause = 0;
				}
			}
			break;
			}

			//If interface register, send the event
			if (m_pAutoEvent) m_pAutoEvent->OnInputAutoEvent(&m_PlayerInput);
	//	}

		//unlock the sem
		ReleaseSemaphore(m_hSemLock, 1, NULL);
		SDL_Delay(5);
	}

}