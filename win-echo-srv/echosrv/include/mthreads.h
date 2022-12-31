#pragma once

#include <windows.h>

#define tid unsigned long

class mthreads{
  HANDLE * threadTable = nullptr;
  tid * tidTable = nullptr;

  unsigned int max_threads = 0;
  unsigned int threadCount = 0;



  public:

    mthreads(unsigned int max_threads);
    

};  