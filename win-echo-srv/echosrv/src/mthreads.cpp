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