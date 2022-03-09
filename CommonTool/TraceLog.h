#ifndef TraceLog_H
#define TraceLog_H
#include <windows.h> 
#include <iostream>
#include <ostream>
#include <fstream>

#include "DebugLogAPI.h"
using namespace std;

#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)



const int FILE_MAX_SIZE = 256;
class CTraceLog: public IDebugLog
{
    public:

        CTraceLog();
        CTraceLog(const char* pTraceFileName, ETraceLevel level= ETraceLevel::TRACE_LVL_PRINTF );
        CTraceLog(unsigned int l_uiNbLine);
        CTraceLog(const char* pTraceFileName,unsigned int l_uiNbLine);
        ~CTraceLog();

       virtual void WriteLog(ETraceLevel l_Tlevel, const char* pTraceLog, const char* pFileName, unsigned int LineNb);
	   virtual void SetTraceLevel(ETraceLevel);
	   virtual void SetTraceFileName(const char* pTraceFileName);
       // void SetConsoleEnable(bool l_bIsConsoleEnable);

    private:
    //Private function
      //  bool RenameFile();
        bool CreateLogFile();
        void GetDateAndTime( char* pTime );
        void GetDateAndTime2( char* pTime );
        bool IsFileExists(const char *filename);
        bool IsTraceToWrite(ETraceLevel l_tracelvl);
        void WriteTrace(ETraceLevel l_Tlevel, const char* pTraceLog, const char* pFileName, unsigned int LineNb);
        bool OpenTraceLogFile(const char*);

    //Private parameter
        ETraceLevel m_TraceLevel;
        char m_pTraceFileName[FILE_MAX_SIZE];
        unsigned int m_uiNbLine;
        unsigned int m_uiLineCounter;
       // bool m_bIsConsoleEnable;
        bool m_bIsFileOpen;
        CRITICAL_SECTION m_csTraceLock;

    //File data
        ofstream m_TraceLog;

        static const char*  c_LevelStr[];
        static const char  c_Extension[];

};

#endif //TraceLog_H
