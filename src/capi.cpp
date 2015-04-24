#include "humblelogging/capi.h"
#include "humblelogging/factory.h"
#include "humblelogging/logger.h"
#include "humblelogging/logevent.h"

LOGGERHANDLE hl_logger_create(const char *name)
{
  humble::logging::Logger& logger = humble::logging::Factory::getInstance().getLogger(std::string(name));
  return &logger;
}

int hl_logger_would_log(LOGGERHANDLE handle, int level)
{
  humble::logging::Logger *logger = static_cast<humble::logging::Logger*>(handle);
  return logger->wouldLog(level) ? 1 : 0;
}

void hl_logger_log(LOGGERHANDLE handle, int level, const char *message, int line, const char *file, const char *func)
{
  humble::logging::Logger *logger = static_cast<humble::logging::Logger*>(handle);
  humble::logging::LogEvent le(level, std::string(message), line, std::string(file), std::string(func));
  logger->log(le);
}
