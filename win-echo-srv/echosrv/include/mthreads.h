#pragma once

#include <windows.h>


#undef tid
#undef mthread
#undef mthreadFunction

#define tid unsigned long

#ifdef WIN32
# define mthread HANDLE
# define mthreadFunction DWORD
#elif defined (linux)
# define mthread pthread_t
# define mthreadFuncion void *

#endif


class mthreads{
  mthread * threadTable = nullptr;
  tid * tidTable = nullptr;

  unsigned int max_threads = 0;
  unsigned int threadCount = 0;

  void updateThreadTable(mthread newThread, tid newTid);


  public:

    ~mthreads();
    mthreads(unsigned int max_threads);
    
    mthread mCreateThread(mthreadFunction (*fn)(void*), void * args, tid * retTid);
    void mDestroySingleThread(mthread thrd);    
    void mDestroyThreads();

};  