#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>

//A singleton logger
class Logger {
  Logger();
  Logger(const Logger&) = delete;
  void operator =(const Logger&) = delete;

  void logTimestamp();

  std::string logfile;

  template<class T> void log(T, bool = true);
  void log(bool, bool = true);
  template<class T> void log(std::vector<T>, bool = true);

  public:
    static Logger& getLogger();    
    std::string getLogfile();

    template<class T> friend void log(T);
};


#endif
