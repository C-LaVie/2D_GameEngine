#ifndef _CONFIGURATION_ACCESS_API_H_
#define _CONFIGURATION_ACCESS_API_H_

#ifdef COMMONTOOL_EXPORTS
#define CONF_ACCESS_API __declspec(dllexport)
#else
#define CONF_ACCESS_API __declspec(dllimport)
#endif


class IConfAccess
{
public:
	virtual int GetintValue(char* Node, char* KeyName) = 0;
	virtual bool GetboolValue(char* Node, char* KeyName) = 0;
	virtual char* GetStringValue(char* Node, char* KeyName) = 0;
};

namespace nsCGEE
{
	class CConfAccessAPI
	{
		static IConfAccess* GetConfAccess(char* pConfFile);
	};
}



#endif //_CONFIGURATION_ACCESS_API_H_
