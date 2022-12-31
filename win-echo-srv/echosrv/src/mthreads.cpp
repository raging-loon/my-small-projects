#include <windows.h>
#include "mthreads.h"
#include <stdlib.h>

mthreads::mthreads(unsigned int max_threads) : max_threads(max_threads)
{
  threadTable = (HANDLE *)malloc(sizeof(HANDLE) * max_threads);
  tidTable = (tid *)malloc(sizeof(tid) * max_threads);

  memset(threadTable, 0, sizeof(HANDLE) * max_threads);
  memset(tidTable, 0, sizeof(tid) * max_threads);


}

mthread mthreads::mCreateThread(mthreadFunction (*fn)(void*), void * args, tid * retTid)
{
  // in case NULL is assigned for retTid, we still need it
  tid ttid;
  mthread retHandle = CreateThread(
    NULL,
    0,
    fn,
    args,
    0,
    &ttid
  );

  threadTable[threadCount++] = retHandle;
  tidTable[threadCount++] = ttid;

  if(retTid) *retTid = ttid;
  return retHandle;
}
    
void mthreads::mDestroyThreads()
{
  for(int i = 0; i < max_threads; i++)
  {
    if(threadTable[i]) CloseHandle(threadTable[i]);
  }
}





void mthreads::updateThreadTable(mthread newThread, tid newTid)
{
  for(int i = 0; i < max_threads; i++)
  {
    if(threadTable[i] == NULL)
    {
      threadTable[i] = newThread;
      tidTable[i] = newTid;
    }
  }


}
void mthreads::mDestroySingleThread(mthread thrd)
{
  
} 



mthreads::~mthreads()
{ 
  mDestroyThreads();
}


