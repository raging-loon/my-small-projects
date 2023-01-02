#include "mlog.h"

#include <iostream>
#include <ctime>
#include <sstream>

using namespace std;

mlog::mlog(std::string filename, unsigned int flags) : flags(flags), logFilename(filename)
{
}



int mlog::init()
{
  output = std::ofstream(logFilename);

  if(!output.good()) return -1;

  return 0;
  
}

char * mlog::logLevelToStr(mlog_log_level l)
{
  switch(l)
  {
    case mlog_log_level::ML_INFO: return "INFO";
    case mlog_log_level::ML_STATUS: return "STATUS";
    case mlog_log_level::ML_WARNING: return "WARNING";
    case mlog_log_level::ML_CRITICAL: return "CRITICAL";
    case mlog_log_level::ML_ERROR: return "ERROR";
    default: return "?";
  }
}


std::string mlog::getCurrentTime()
{
  time_t t = time(0);

  tm * now = localtime(&t);

  ostringstream builder;

  builder << (now->tm_year + 1900) << '-'
          << (now->tm_mon + 1) << '-'
          << now->tm_mday << " "
          << now->tm_hour << ":"
          << now->tm_min << ":"
          << now->tm_sec;


  return builder.str();
}

void mlog::write(const mlog_log_level logLevel, std::string message)
{
  output << getCurrentTime() << " "
       << logLevelToStr(logLevel) << " "
       << message << endl;
}



mlog::~mlog()
{
  if(output.is_open()) output.close();
}
