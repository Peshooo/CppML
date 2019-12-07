#include "Logger.h"
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>

Logger::Logger() {
  std::stringstream filename;

  filename<<"logs_"<<std::time(0)<<".logfile";
  
  logfile = filename.str();
}

Logger& Logger::getLogger() {
  static Logger logger;
  return logger;
}

void Logger::logTimestamp() {
  std::ofstream out(logfile.c_str(), std::ios_base::app);
  
  out<<"[ Time: "<<time(0)<<" ]"<<"   ";
}

template<class T> void Logger::log(T item, bool topLevel) {
  std::ofstream out(logfile.c_str(), std::ios_base::app);
  
  if(topLevel) {
    logTimestamp();
  }

  out<<item;
  
  
  if(topLevel) {
    out<<std::endl;
  }
}

void Logger::log(bool item, bool topLevel) {
  std::ofstream out(logfile.c_str(), std::ios_base::app);
  
  if(topLevel) {
    logTimestamp();
  }

  if(item==false) {
    out<<"false";
  } else {
    out<<"true";
  }

  if(topLevel) {
    out<<std::endl;
  }
}

template<class T> void Logger::log(std::vector<T> item, bool topLevel) {
  std::ofstream out(logfile.c_str(), std::ios_base::app);
  
  if(topLevel) {
    logTimestamp();
  }

  bool firstItem = true;
  out<<"{";
  for(T currentItem: item) {
    if(!firstItem) {
      out<<", ";
    } else {
      firstItem = false;
    }

    log(currentItem, false);
  }
  out<<"}";

  if(topLevel) {
    out<<std::endl;
  }
}

std::string Logger::getLogfile() {
  return logfile;
}

template<class T> void log(T t) {
  Logger::getLogger().log(t);
}
