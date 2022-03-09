#include <windows.h> 
#include <iostream>
#include <ostream>
#include <fstream>
#include "Configuration.h"



CConfigurationAccess::CConfigurationAccess(char* pFile)
{
	sprintf_s(m_pConfFile, pFile, strlen(pFile));
	InitializeCriticalSection(&m_csLock);
}

CConfigurationAccess::~CConfigurationAccess()
{
	DeleteCriticalSection(&m_csLock);
}

int CConfigurationAccess::GetintValue(char* Node, char* KeyName)
{
	int Temp = 0;
	EnterCriticalSection(&m_csLock);
	Temp = GetPrivateProfileIntA(Node, KeyName, 0, m_pConfFile);
	LeaveCriticalSection(&m_csLock);

	return Temp;
}

bool CConfigurationAccess::GetboolValue(char* Node, char* KeyName)
{
	bool Temp = 0;
	EnterCriticalSection(&m_csLock);
	Temp = (bool) GetPrivateProfileIntA(Node, KeyName, 0, m_pConfFile);
	LeaveCriticalSection(&m_csLock);

	return Temp;
}

char* CConfigurationAccess::GetStringValue(char* Node, char* KeyName)
{
	char Temp[256] = { 0 };

	EnterCriticalSection(&m_csLock);
	GetPrivateProfileStringA(Node, KeyName,Temp, "",255, m_pConfFile);
	LeaveCriticalSection(&m_csLock);

	return Temp;
}