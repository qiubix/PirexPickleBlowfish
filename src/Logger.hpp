#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <boost/log/trivial.hpp>

#define LOG(lvl) BOOST_LOG_TRIVIAL(lvl)

void initLogging(void);
void initConsoleLog(boost::log::trivial::severity_level);
void initFileLog(boost::log::trivial::severity_level);
void setLoggingEnabled(bool);

#endif // LOGGER_HPP
