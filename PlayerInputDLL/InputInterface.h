#ifndef _PLAYER_INPUT_INTERFACE_H_
#define _PLAYER_INPUT_INTERFACE_H_

#include "InputAPI.h"


using namespace PlayerInputAPI;


class CInputInterface :public IPlayerInputAPI
{
	public:
		CInputInterface();
		~CInputInterface();
		virtual void GetInput(stPlayerInput& Input) ;
		virtual void SetOnAutoEventInter(IPlayerInputOnAutoEvent*p);
		virtual void ReloadKeyMap();

};

#endif //_PLAYER_INPUT_INTERFACE_H_