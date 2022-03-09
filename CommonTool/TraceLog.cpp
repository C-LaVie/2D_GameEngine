#include <stdio.h>
#include <stdlib.h>
//#include <sys/time.h>
#include <time.h>
#include <string.h>

#include "TraceLog.h"

const char CTraceLog::c_Extension[]=".txt";
const char * CTraceLog::c_LevelStr[]		= {	"NONE   ",
                                                "ERROR  ",
                                                "WARNING",
                                                "INFO   ",
                                                "DEBUG  ",
                                                "PRINTF " };

extern "C" CTraceLog* create_object( )
{
  return new CTraceLog;
}

extern "C" void destroy_object( CTraceLog* object )
{
  delete object;
}

CTraceLog::CTraceLog()
{
    m_TraceLevel = ETraceLevel::TRACE_LVL_NONE;
    m_uiNbLine = 1000;
   // m_bIsConsoleEnable = false;
    memset(m_pTraceFileName,0,sizeof(m_pTraceFileName));
	InitializeCriticalSection(&m_csTraceLock);
    m_bIsFileOpen = false;
}
CTraceLog::~CTraceLog()
{
    if(m_bIsFileOpen)
    {
        m_TraceLog.flush();
        m_TraceLog.close();
        m_bIsFileOpen = false;
    }

	DeleteCriticalSection(&m_csTraceLock);

}


CTraceLog::CTraceLog(const char* pTraceFileName, ETraceLevel level)
{
    m_TraceLevel = level;
    m_uiNbLine = 1000;
    m_uiLineCounter = 0;
   // m_bIsConsoleEnable = false;
   m_bIsFileOpen = false;
    memset(m_pTraceFileName,0,sizeof(m_pTraceFileName));
    memcpy(m_pTraceFileName,pTraceFileName,min(sizeof(m_pTraceFileName),strlen(pTraceFileName)));
	InitializeCriticalSection(&m_csTraceLock);
}
CTraceLog::CTraceLog(unsigned int l_uiNbLine)
{
    m_TraceLevel = ETraceLevel::TRACE_LVL_NONE;
    m_uiNbLine = l_uiNbLine;
    m_uiLineCounter = 0;
   // m_bIsConsoleEnable = false;
   m_bIsFileOpen = false;
    memset(m_pTraceFileName,0,sizeof(m_pTraceFileName));
	InitializeCriticalSection(&m_csTraceLock);

}
CTraceLog::CTraceLog(const char* pTraceFileName,unsigned int l_uiNbLine)
{
    m_TraceLevel = ETraceLevel::TRACE_LVL_NONE;
    m_uiNbLine = l_uiNbLine;
    m_uiLineCounter = 0;
   // m_bIsConsoleEnable = false;
   m_bIsFileOpen = false;
    memset(m_pTraceFileName,0,sizeof(m_pTraceFileName));
    memcpy(m_pTraceFileName,pTraceFileName,min(sizeof(m_pTraceFileName),strlen(pTraceFileName)));
	InitializeCriticalSection(&m_csTraceLock);
}

void CTraceLog::WriteLog(ETraceLevel l_Tlevel, const char* pTraceLog, const char* pFileName, unsigned int LineNb)
{
	EnterCriticalSection(&m_csTraceLock);
    //Check if the trace has to be write
    if(IsTraceToWrite(l_Tlevel))
    {
        if(!m_bIsFileOpen )
        {
            if(CreateLogFile())
            {
                WriteTrace(l_Tlevel,pTraceLog,pFileName,LineNb);
            }
        }
        else if(( m_uiLineCounter > m_uiNbLine))
        {
            //Close, rename the file and create a new empty one
            m_TraceLog.close();
            m_bIsFileOpen = false;
            if(CreateLogFile())
            {
                WriteTrace(l_Tlevel,pTraceLog,pFileName,LineNb);
            }

        }
        else
        {
            WriteTrace(l_Tlevel,pTraceLog,pFileName,LineNb);
        }

    }
	LeaveCriticalSection(&m_csTraceLock);
}

void CTraceLog::SetTraceLevel(ETraceLevel l_Tracelvl)
{
    m_TraceLevel = l_Tracelvl;
}
/*
void CTraceLog::SetConsoleEnable(bool l_bIsConsoleEnable)
{
    m_bIsConsoleEnable = l_bIsConsoleEnable;
}*/

void CTraceLog::SetTraceFileName(const char* pTraceFileName)
{
    memset(m_pTraceFileName,0,sizeof(m_pTraceFileName));
    memcpy(m_pTraceFileName,pTraceFileName,min(sizeof(m_pTraceFileName),strlen(pTraceFileName)));

}
bool CTraceLog::CreateLogFile()
{
    bool l_result = false;
    // create the full name + extention
	char FullName[256] = {0};// (char*)malloc(strlen(m_pTraceFileName) + 1 + 4);
    // copy name into the new var
	
    strcpy_s(FullName,(const char*) m_pTraceFileName);

    // add the extension
    strcat_s(FullName, c_Extension);

    //First check if the file is existing
    if(IsFileExists(FullName))
    {
        //Rename the file
        //Check time to add to the string
        char NewName[256] = {0};
        GetDateAndTime2(NewName);
      //  char* FullNewName = (char*)malloc(strlen(m_pTraceFileName)+ strlen(NewName)+1+4);
		char FullNewName[256] = { 0 };
        strcpy_s(FullNewName, m_pTraceFileName);
        // add the date and time
        strcat_s(FullNewName, NewName);
        // add the extension
        strcat_s(FullNewName, c_Extension);
        //Success
        if((rename(FullName,FullNewName)) == 0)
        {
            l_result = OpenTraceLogFile(FullName);
        }
   //     free(FullNewName);
    }
    else
    {
        l_result = OpenTraceLogFile(FullName);
    }
  //  free(FullName);
    return l_result;
}
bool CTraceLog::IsFileExists(const char *filename)
{
  ifstream ifile(filename);
  return (bool)ifile;
}

void CTraceLog::GetDateAndTime( char* pTime )
{
	SYSTEMTIME l_systemtime;
	GetLocalTime(&l_systemtime);
	char cTime[256] = { 0 };
	sprintf_s(cTime, "%02d/%02d/%02d %02d:%02d:%02d, %03d" ,
				l_systemtime.wMonth,
				l_systemtime.wDay,
				l_systemtime.wYear % 100,
				l_systemtime.wHour,
				l_systemtime.wMinute,
				l_systemtime.wSecond,
				l_systemtime.wMilliseconds);
  /*  timeval tp;
    gettimeofday(&tp, 0);
    time_t curtime = tp.tv_sec;
    tm *t = localtime(&curtime);
    //Here to get the date
    time_t daytime= time(NULL);
    struct tm tm = *localtime(&daytime);
    //wrape the data into the array of char
    sprintf( pTime,"%02d/%02d/%02d %02d:%02d:%02d, %03d",tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, t->tm_hour, t->tm_min, t->tm_sec, tp.tv_usec/1000);
	*/
	memcpy(pTime, cTime, 256);
}

void CTraceLog::GetDateAndTime2( char* pTime )
{
	SYSTEMTIME l_systemtime;
	GetLocalTime(&l_systemtime);
	char cTime[256] = { 0 };
	sprintf_s(cTime, "%02d_%02d_%02d_%02d_%02d_%02d_%03d" ,
				l_systemtime.wYear % 100,
				l_systemtime.wMonth,
				l_systemtime.wDay,
				l_systemtime.wHour,
				l_systemtime.wMinute,
				l_systemtime.wSecond,
				l_systemtime.wMilliseconds);

	memcpy(pTime, cTime, 256);
   /* timeval tp;
    gettimeofday(&tp, 0);
    time_t curtime = tp.tv_sec;
    tm *t = localtime(&curtime);
    //Here to get the date
    time_t daytime = time(NULL);
    struct tm tm = *localtime(&daytime);
    //wrape the data into the array of char
    sprintf( pTime,"%02d_%02d_%02d_%02d_%02d_%02d_%03d",tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, t->tm_hour, t->tm_min, t->tm_sec, tp.tv_usec/1000);
*/
}

bool CTraceLog::IsTraceToWrite(ETraceLevel l_tracelvl)
{
    return (l_tracelvl <= m_TraceLevel)?true:false;
}

void CTraceLog::WriteTrace(ETraceLevel l_Tlevel, const char* pTraceLog, const char* pFileName, unsigned int LineNb)
{
    char Buffer[256] = {0};
    GetDateAndTime(Buffer);
    m_TraceLog<<Buffer << "    "<<pFileName<<"  ["<<LineNb<<" "
    << c_LevelStr[(int)l_Tlevel] <<"] " << pTraceLog<<endl;
    m_TraceLog.flush();
    ++m_uiLineCounter;
}

bool CTraceLog::OpenTraceLogFile(const char*pName)
{
    bool l_result = false;
    if(m_TraceLog.is_open())
    {
        m_TraceLog.close();
    }

    m_TraceLog.open (pName,ios::out | ios::app);
    if (m_TraceLog.is_open())
    {
        m_uiLineCounter = 0;
        m_bIsFileOpen = true;
        l_result = true;
    }
    return l_result;
}
