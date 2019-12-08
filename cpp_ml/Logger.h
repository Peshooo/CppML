#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>

//A singleton logger
class Logger {
  class Loggable {
    std::stringstream stream;

    public:
      Loggable();
      Loggable(bool);
      Loggable(Matrix);
      Loggable(const Loggable&);
      template<class T> Loggable(std::vector<T>);
      template<class T> Loggable(T);

      void operator =(const Loggable&);
      Loggable& operator +=(const Loggable&);

      std::string getValue() const;
  };
  
  std::string logfile;
  double startingTime;

  Logger();
  Logger(const Logger&) = delete;

  void operator =(const Logger&) = delete;

  void logTimestamp(bool);

  void log(Loggable, bool);

  public:
    static Logger& getLogger();    
    std::string getLogfile();

    friend void logMessage(std::vector<Loggable>, bool);
    friend void logMessage(std::vector<Loggable>);
};
#endif
