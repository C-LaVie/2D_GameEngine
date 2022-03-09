#ifndef _DEBUG_Log_H_
#define _DEBUG_Log_H_

#ifdef COMMONTOOL_EXPORTS
#define TRACE_LOG_EXP __declspec(dllexport) 
#else
#define TRACE_LOG_EXP __declspec(dllimport) 
#endif

enum class ETraceLevel : unsigned int
{
	TRACE_LVL_NONE = 0,		///No trace won't be performed
	TRACE_LVL_ERROR,		///Only Error calls will be considered
	TRACE_LVL_WARNING,		///trace will consider function call starting from warning level to none
	TRACE_LVL_INFORMATION,	///trace will consider function call starting from info level to none
	TRACE_LVL_DEBUG,		///trace will consider function call starting from debug level to none
	TRACE_LVL_PRINTF		///trace will consider all its received calls
};


class IDebugLog
{
public :
	virtual void WriteLog(ETraceLevel l_Tlevel, const char* pTraceLog, const char* pFileName, unsigned int LineNb) = 0;
	virtual void SetTraceLevel(ETraceLevel) = 0;
	virtual void SetTraceFileName(const char* pTraceFileName) = 0;
};

namespace nsCGEE
{
	class TRACE_LOG_EXP CDebugLog
	{
	public:
		static IDebugLog* GetDebugLog(char* pName, ETraceLevel level = ETraceLevel::TRACE_LVL_PRINTF);
	};
}


#endif
