#ifndef _INPUT_H_
#define _INPUT_H_

#include <iostream>



#ifdef PLAYERINPUTDLL_EXPORTS
#define _FUNCDLL_ extern "C" __declspec(dllexport) 
#else
#define _FUNCDLL_ extern "C" __declspec(dllimport) 
#endif


typedef struct
{
	int Left;
	int Right;
	int Up;
	int Down;
	int Enter;
	int Erase;
	int Pause;
	int Mouse_X;
	int Mouse_Y;
	int Mouse_Click;
	//Special key to map any kind of action you wishes, like hit, fire, menu, etc...
	int control_Key_0;
	int control_Key_1;
	int control_Key_2;
	int control_Key_3;
	int control_Key_4;
	int control_Key_5;
	int control_Key_6;
	int control_Key_7;
	int control_Key_8;
	int control_Key_9;

} stPlayerInput;


namespace PlayerInputAPI
{
	class IPlayerInputOnAutoEvent
	{
		public:
			virtual void OnInputAutoEvent(stPlayerInput* pInput) = 0;
	};
	class IPlayerInputAPI
	{
		public:
			//Polling status
			virtual void GetInput(stPlayerInput& Input) = 0;
			virtual void ReloadKeyMap() = 0;

			//Auto event on event detection the event is send to the p pointer class
			virtual void SetOnAutoEventInter(IPlayerInputOnAutoEvent* p) = 0;
	};

	typedef IPlayerInputAPI* (*GETINPUTINTERFACE)();
	#define GETINPUTINTER_NAME "GetInputInterface"
	_FUNCDLL_ IPlayerInputAPI* GetInputInterface();



}
#endif //_INPUT_H_