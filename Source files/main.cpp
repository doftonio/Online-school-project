#include "../Header files/faculty.h"
#include "../Header files/menu.h"
#include "../Storage/fileStorageService.h"
#include "../Storage/logger.h"
#include "../Exceptions/exceptions.h"
#include <iostream>
#include <filesystem>
#include <format>

int main() {
    Faculty faculty("Faculty of Computer Systems and Networks");

    try {
        Logger::info("Application started.");
        if (std::filesystem::exists(FileStorageService::AUTOSAVE_FILE)) {
            FileStorageService::loadState(faculty, FileStorageService::AUTOSAVE_FILE);
            Logger::info(std::format("Restored previous session state from \"{}\".",
                                     FileStorageService::AUTOSAVE_FILE));
            std::cout << "Previous session state automatically restored from \""
                      << FileStorageService::AUTOSAVE_FILE << "\".\n";
        } else {
            Logger::info("No previous autosave found. Starting with an empty state.");
        }
    } catch (const AppException& ex) {
        std::cerr << "[Startup Warning] " << ex.what() << "\n";
    }

    runMainMenu(faculty);

    try {
        Logger::info("Application terminated normally.");
    } catch (const AppException& ex) {
        std::cerr << "[Shutdown Warning] " << ex.what() << "\n";
    }

    return 0;
}
