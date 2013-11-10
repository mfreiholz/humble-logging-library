#include "formatter.h"

#include <sstream>

#include "loglevel.h"

namespace humble {
namespace logging {

///////////////////////////////////////////////////////////////////////////////
// Formatter
///////////////////////////////////////////////////////////////////////////////

Formatter::Formatter()
{
}

Formatter::~Formatter()
{
}

///////////////////////////////////////////////////////////////////////////////
// SimpleFormatter
///////////////////////////////////////////////////////////////////////////////

SimpleFormatter::SimpleFormatter()
{
}

SimpleFormatter::~SimpleFormatter()
{
}

Formatter* SimpleFormatter::copy() const
{
  return new SimpleFormatter(*this);
}

std::string SimpleFormatter::format(const LogEvent &logEvent) const
{
  std::string logLevelString = LogLevel::resolveLogLevel(logEvent.getLogLevel());

  struct tm *timeinfo = localtime(&logEvent.getTime());
  char timeString [80];
  strftime(timeString, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
  
  std::stringstream ss;
  ss
    << "[" << timeString << "] "
    << "[" << logLevelString << "] "
    << "[line=" << logEvent.getLine() << "] "
    << "[file=" << logEvent.getFile() << "] "
    << logEvent.getMessage()
    << "\n";
  return ss.str();
}

///////////////////////////////////////////////////////////////////////////////
// PatternFormatter
///////////////////////////////////////////////////////////////////////////////

PatternFormatter::PatternFormatter(const std::string &pattern)
  : _pattern(pattern)
{
}

PatternFormatter::PatternFormatter(const PatternFormatter &other)
{
  _pattern = other._pattern;
}

PatternFormatter::~PatternFormatter()
{
}

Formatter* PatternFormatter::copy() const
{
  return new PatternFormatter(*this);
}

std::string PatternFormatter::format(const LogEvent &logEvent) const
{
  std::string s = _pattern;
  size_t pos = std::string::npos;
  if ((pos = s.find("%lls")) != std::string::npos) {
    const std::string lls = LogLevel::resolveLogLevel(logEvent.getLogLevel());
    s.replace(pos, 4, lls);
  }
  if ((pos = s.find("%m")) != std::string::npos) {
    s.replace(pos, 2, logEvent.getMessage());
  }
  if ((pos = s.find("%line")) != std::string::npos) {
    char buff[10];
    sprintf(buff, "%d", logEvent.getLine());
    s.replace(pos, 5, buff);
  }
  if ((pos = s.find("%file")) != std::string::npos) {
    s.replace(pos, 5, logEvent.getFile());
  }
  if ((pos = s.find("%date")) != std::string::npos) {
    struct tm *timeinfo = localtime(&logEvent.getTime());
    char timeString [80];
    strftime(timeString, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
    s.replace(pos, 5, timeString);
  }
  return s;
}

}}  // End of namespaces.