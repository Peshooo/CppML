#include "LoggerFactory.h"
#include <sstream>
#include <ctime>

LoggerFactory::LoggerFactory() {
  std::stringstream filename;

  filename<<"logs"<<time(0)<<".logfile";

  out(filename);
  logger = new Logger(out);
}
