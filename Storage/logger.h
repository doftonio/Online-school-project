#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <string_view>
#include <vector>

class Logger {
public:
    static constexpr std::string_view DEFAULT_LOG_FILE = "Storage/data/system_log.txt";

    static void info(std::string_view message, std::string_view logPath = DEFAULT_LOG_FILE);
    static void warn(std::string_view message, std::string_view logPath = DEFAULT_LOG_FILE);
    static void error(std::string_view message, std::string_view logPath = DEFAULT_LOG_FILE);
    static std::vector<std::string> readEntries(std::string_view logPath = DEFAULT_LOG_FILE);

private:
    static void writeEntry(std::string_view level, std::string_view message, std::string_view logPath);
    static std::string currentTimestamp();
};

#endif
