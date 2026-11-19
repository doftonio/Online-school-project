#ifndef FILE_STORAGE_SERVICE_H
#define FILE_STORAGE_SERVICE_H

#include <string>
#include <string_view>
#include <vector>
#include "../Header files/faculty.h"

class FileStorageService {
public:
    static constexpr std::string_view STORAGE_DIR = "Storage/data";
    static constexpr std::string_view AUTOSAVE_FILE = "Storage/data/autosave_state.txt";
    static constexpr std::string_view DEFAULT_MANUAL_FILE = "Storage/data/manual_save.txt";
    static constexpr std::string_view DEFAULT_REPORT_FILE = "Storage/data/system_report.txt";

    static std::string resolveStoragePath(std::string_view filePath);
    static void ensureDirectoryForFile(std::string_view filePath);

    static std::string saveState(const Faculty& faculty, std::string_view filePath = AUTOSAVE_FILE);
    static std::string loadState(Faculty& faculty, std::string_view filePath = AUTOSAVE_FILE);
    static std::string exportReport(const Faculty& faculty, std::string_view filePath = DEFAULT_REPORT_FILE);

private:
    static void validateFilePath(std::string_view filePath);
    static void validateField(std::string_view value, std::string_view fieldName);
    static std::vector<std::string> splitRecord(const std::string& line, char delimiter = '|');
    static int parseIntField(std::string_view token, std::size_t lineNumber, std::string_view fieldName);
    static void parseActivityRecord(Faculty& targetFaculty, const std::vector<std::string>& tokens, std::size_t lineNumber);
};

#endif
