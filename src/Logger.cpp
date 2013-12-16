#include "Logger.hpp"
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/support/date_time.hpp>

namespace logging = boost::log;
namespace keywords = logging::keywords;
namespace expressions = logging::expressions;
namespace trivial = logging::trivial;

void initLogging(void)
{
  initConsoleLog();
  initFileLog();
  logging::add_common_attributes();

  //disable logging:
  //logging::core::get() -> set_logging_enabled(false);
}

void initConsoleLog(void)
{
  logging::add_console_log
  (
    std::clog,
    keywords::format =
    (
      expressions::stream
        << expressions::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S")
        << ": <" << trivial::severity
        << "> " << expressions::smessage
    )
  ) -> set_filter( trivial::severity >= trivial::trace );
}

void initFileLog(void)
{
  logging::add_file_log
  (
    keywords::file_name = "log_%Y-%m-%d_%H:%M:%S.log",
    keywords::format =
    (
      expressions::stream
        << expressions::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S")
        << ": <" << trivial::severity
        << "> " << expressions::smessage
    ),
    keywords::target = "../logs"
  ) -> set_filter( trivial::severity >= trivial::trace );
}
