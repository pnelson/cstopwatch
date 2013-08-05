#ifndef _STOPWATCH_H
#define _STOPWATCH_H

#include <Windows.h>

class CStopwatch
{
public:
  CStopwatch()
  {
    m_hThread = NULL;

    m_bStart = FALSE;
    m_dwLast = 0;
    m_dwElapsed = 0;
  }

  virtual ~CStopwatch()
  {
    if (m_hThread)
    {
      ::TerminateThread(m_hThread, EXIT_SUCCESS);
      ::CloseHandle(m_hThread);
    }
  }

  BOOL Initialize()
  {
    m_hThread = ::CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)CStopwatch::StopwatchProc, this, NULL, NULL);

    if (!m_hThread)
      return FALSE;

    return TRUE;
  }

  BOOL Start()
  {
    if (!m_hThread)
      return FALSE;

    m_dwLast = ::GetTickCount();
    m_bStart = TRUE;

    ::_tprintf_s(_T("Starting: %d\n"), m_dwElapsed);

    return TRUE;
  }

  BOOL Stop()
  {
    if (!m_hThread)
      return FALSE;

    m_bStart = FALSE;

    return TRUE;
  }

  BOOL Reset()
  {
    if (!m_hThread)
      return FALSE;

    m_bStart = FALSE;
    m_dwLast = 0;

    m_dwElapsed = 0;

    return TRUE;
  }

  DWORD GetElapsedMilliseconds()
  {
    return m_dwElapsed;
  }

protected:
  static BOOL CALLBACK StopwatchProc(LPVOID lpParam)
  {
    CStopwatch* pStopwatch = (CStopwatch*)lpParam;

    while (TRUE)
    {
      ::Sleep(100);

      if (!pStopwatch->m_bStart)
        continue;

      pStopwatch->m_dwElapsed += ::GetTickCount() - pStopwatch->m_dwLast;
      pStopwatch->m_dwLast = ::GetTickCount();
    }

    return TRUE;
  }

private:
  HANDLE m_hThread;

  BOOL m_bStart;
  DWORD m_dwLast;
  DWORD m_dwElapsed;
};

#endif
