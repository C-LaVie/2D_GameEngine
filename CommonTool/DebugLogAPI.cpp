
#include "DebugLogAPI.h"
#include "TraceLog.h"

using namespace nsCGEE;



IDebugLog* CDebugLog::GetDebugLog(char* pName, ETraceLevel level)
{
	return (IDebugLog*) new CTraceLog(pName, level);
}