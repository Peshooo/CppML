#include "Logger.h"
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>

Logger::Loggable::Loggable() {
  stream = std::stringstream();
}

Logger::Loggable::Loggable(bool b) {
  stream = std::stringstream();

  if(b==false) {
    stream<<"false";
  } else {
    stream<<"true";
  }
}

template<class T> Logger::Loggable::Loggable(T t) {
  stream = std::stringstream();

  stream<<t;
}

template<class T> Logger::Loggable::Loggable(std::vector<T> v) {
  stream = std::stringstream();
  bool first = true;

  stream<<"{";

  for(T curr: v) {
    if(!first) {
      stream<<", ";
    } else {
      first = false;
    }

    *this += curr;
  }

  stream<<"}";
}

Logger::Loggable::Loggable(Matrix x) {
  stream = std::stringstream();

  stream<<"Matrix"<<std::endl;
  stream<<"Rows = "<<x.getRows()<<std::endl;
  stream<<"Cols = "<<x.getCols()<<std::endl;
  stream<<"{"<<std::endl;
  for(int i=0;i<x.getRows();i++) {
    stream<<" {";
    for(int j=0;j<x.getCols();j++) {
      if(j>0) {
        stream<<", ";
      }

      stream<<x[i][j];
    }
    stream<<"}"<<std::endl;
  }
  stream<<"}"<<std::endl;
}

Logger::Loggable::Loggable(const Loggable& x) {
  stream = std::stringstream(x.getValue());
}

void Logger::Loggable::operator =(const Loggable& x) {
  stream = std::stringstream(x.getValue());
}

Logger::Loggable& Logger::Loggable::operator +=(const Loggable& x) {
  stream<<x.getValue();
  return *this;
}

std::string Logger::Loggable::getValue() const {
  return stream.str();
}

Logger::Logger() {
  std::stringstream filename;

  filename<<"logs_"<<std::time(0)<<".logfile";

  logfile = filename.str();
}

Logger& Logger::getLogger() {
  static Logger logger;
  return logger;
}

void Logger::logTimestamp(bool replicateToCerr) {
  std::ofstream out(logfile.c_str(), std::ios_base::app);

  unsigned long long elapsedTime = (unsigned long long) (1000.0 * (clock() - startingTime) / CLOCKS_PER_SEC);

  out<<"[Time: "<<elapsedTime<<" ms]"<<" ";
  if(replicateToCerr) {
    std::cerr<<"[Time: "<<elapsedTime<<" ms]"<<" ";
  }
}

std::string Logger::getLogfile() {
  return logfile;
}

void Logger::log(Loggable item, bool replicateToCerr) {
  std::ofstream out(logfile.c_str(), std::ios_base::app);
  
  logTimestamp(replicateToCerr);

  out<<item.getValue();
  out<<std::endl;
  if(replicateToCerr) {
    std::cerr<<item.getValue();
    std::cerr<<std::endl;
  }
}

void logMessage(std::vector<Logger::Loggable> items, bool replicateToCerr) {
  Logger::Loggable item;

  for(Logger::Loggable currentItem: items) {
    item += currentItem;
  }

  Logger::getLogger().log(Logger::Loggable(item), replicateToCerr);
}

void logMessage(std::vector<Logger::Loggable> items) {
  logMessage(items, true);
}
