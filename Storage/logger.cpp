#include "logger.h"
#include "fileStorageService.h"
#include "../Exceptions/exceptions.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <format>

std::string Logger::currentTimestamp() {
    const auto now = std::chrono::system_clock::now();
    const auto seconds = std::chrono::floor<std::chrono::seconds>(now);
    return std::format("{:%Y-%m-%d %H:%M:%S}", seconds);
}

void Logger::writeEntry(std::string_view level, std::string_view message, std::string_view logPath) {
    const std::string formatted = std::format("[{}] [{}] {}", currentTimestamp(), level, message);

    if (level == "ERROR") {
        std::cerr << formatted << "\n";
    } else {
        std::clog << formatted << "\n";
    }

    FileStorageService::ensureDirectoryForFile(logPath);

    std::ofstream logFile{std::string(logPath), std::ios::out | std::ios::app};
    if (!logFile.is_open()) {
        throw FileStorageException(std::format("Unable to open log file for appending: \"{}\".", logPath));
    }

    logFile << formatted << "\n";
    logFile.flush();

    if (logFile.fail() || logFile.bad()) {
        throw FileStorageException(std::format("Failed while writing entry to log file: \"{}\".", logPath));
    }
}

void Logger::info(std::string_view message, std::string_view logPath) {
    writeEntry("INFO", message, logPath);
}

void Logger::warn(std::string_view message, std::string_view logPath) {
    writeEntry("WARN", message, logPath);
}

void Logger::error(std::string_view message, std::string_view logPath) {
    writeEntry("ERROR", message, logPath);
}

std::vector<std::string> Logger::readEntries(std::string_view logPath) {
    std::ifstream logFile{std::string(logPath), std::ios::in};
    if (!logFile.is_open()) {
        throw FileStorageException(std::format("Log file does not exist or cannot be opened: \"{}\".", logPath));
    }

    std::vector<std::string> entries;
    std::string line;
    while (std::getline(logFile, line)) {
        if (!line.empty()) {
            entries.push_back(std::move(line));
        }
    }

    if (logFile.bad()) {
        throw FileStorageException(std::format("I/O error occurred while reading log file: \"{}\".", logPath));
    }

    return entries;
}
