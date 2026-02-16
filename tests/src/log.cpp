#include "tests/includes/log.hpp"
#include <iostream>

namespace la
{
namespace test
{

logger *logger::p_instance = nullptr;

logger::logger() : p_level(DEFAULT_LOG_LEVEL) {}

logger &logger::get()
{
    if (p_instance == nullptr)
    {
        p_instance = new logger();
    }
    return *p_instance;
}

void logger::set_level(const TestLogLevel &level) { p_level = level; }

void logger::log(const std::string &what, const TestLogLevel &level)
{
    if (level <= p_level)
    {
        std::cout << what << std::endl;
    }
}

void logger::log(std::stringstream &what, const TestLogLevel &level)
{
    log(what.str(), level);
    what.str("");
    what.clear();
}

} // namespace test
} // namespace la
