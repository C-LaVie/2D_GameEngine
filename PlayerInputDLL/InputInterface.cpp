#include "InputInterface.h"
#include "InputManager.h"

CInputManager* pManager = NULL;

CInputInterface::CInputInterface()
{
	if (pManager == NULL)
	{
		pManager = new CInputManager;
	}

}

CInputInterface::~CInputInterface()
{

}

void CInputInterface::GetInput(stPlayerInput& input)
{
	if (pManager == NULL)
	{
		pManager = new CInputManager;
	}
	if (pManager) pManager->SDL_GetInput(input);
}

void CInputInterface::SetOnAutoEventInter(IPlayerInputOnAutoEvent*p)
{
	if (pManager == NULL)
	{
		pManager = new CInputManager;
	}
	if (pManager) pManager->SDL_SetOnAutoEventInter(p);
}

void CInputInterface::ReloadKeyMap()
{
	if (pManager == NULL)
	{
		pManager = new CInputManager;
	}
	if (pManager) pManager->ReloadKeyAssignment();
}