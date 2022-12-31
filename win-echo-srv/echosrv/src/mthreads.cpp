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


  updateThreadTable(retHandle, ttid);

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

int mthreads::getThreadIndex(mthread target)
{
  if(!target) return -1;
  for(int i = 0; i < max_threads; i++)
  {
    if(threadTable[i] != NULL && threadTable[i] == target) return i;
  }
  return -1;
}


void mthreads::mDestroySingleThread(mthread thrd)
{
  if(!thrd) return;

  int tIndex = getThreadIndex(thrd);
  
  if(tIndex == -1) return;

  CloseHandle(thrd);

  threadTable[tIndex] = NULL;
  tidTable[tIndex] = 0;

} 



mthreads::~mthreads()
{ 
  mDestroyThreads();
}


