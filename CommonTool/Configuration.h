#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

#include <Windows.h>
#include "ConfigurationAccessAPI.h"

#define MAX_FILE_NAME 256


class  CConfigurationAccess: public IConfAccess
{
	public:
		CConfigurationAccess(char* pConf);
		~CConfigurationAccess();

		virtual int GetintValue(char* Node, char* KeyName);
		virtual bool GetboolValue(char* Node, char* KeyName);
		virtual char* GetStringValue(char* Node, char* KeyName);

	private:

		char m_pConfFile[MAX_FILE_NAME];
		CRITICAL_SECTION m_csLock;
		
};



#endif //_CONFIGURATION_H_


