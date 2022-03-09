#include "ConfigurationAccessAPI.h"
#include "Configuration.h"
using namespace nsCGEE;

IConfAccess* CConfAccessAPI::GetConfAccess(char* pConfFile)
{
	return (IConfAccess*) new CConfigurationAccess(pConfFile);
}