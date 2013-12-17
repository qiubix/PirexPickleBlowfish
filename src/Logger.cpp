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

/*
 * QUESTION: Is it really difficult to add different kind of logging levels?
 * For instance, setting logging level to 0 (let's say it's default) prints only
 * <info> messages with <error> and <fatal> as well.
 * Level 1 adds <warnings>
 * Level 2 adds <trace>
 * Level 3 is for most indepth debuging, so allows also <debug> messages.
 * I've seen it done as a common practise. I've never implemented a logger before,
 * but I've been using a few different ones.
 */

/*
 * QUESTION 2: What do you think about colors in logs? Is it even possible in boost::log?
 */
void initLogging(void)
{
  initConsoleLog();
  initFileLog();
  logging::add_common_attributes();

  //REVIEW: Is it really the only way to disable logs? Maybe some kind of toggleLogging(void) method would be appropriate?
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
