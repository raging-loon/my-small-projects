#pragma once

#include <fstream>
#include <iostream>


#define mlog_flag static const unsigned int


enum class mlog_log_level{
  ML_INFO,
  ML_STATUS,
  ML_WARNING,
  ML_ERROR,
  ML_CRITICAL
};

class mlog{
  std::ofstream output;
  std::string logFilename; 
  unsigned int flags;

  std::string getCurrentTime();
  char * logLevelToStr(mlog_log_level);

public:

  mlog(std::string filename, unsigned int flags);
  int init();
  void write(const mlog_log_level logLevel, std::string message);
  ~mlog();


  // flags
  mlog_flag NONE = 0;
  mlog_flag INCLUDE_TIME = 1;
  mlog_flag COLORIZE = 2;






};

