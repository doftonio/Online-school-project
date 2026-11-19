#ifndef FILE_STORAGE_EXCEPTION_H
#define FILE_STORAGE_EXCEPTION_H

#include <string>
#include <format>
#include "appException.h"

class FileStorageException : public AppException {
public:
    explicit FileStorageException(const std::string& message)
        : AppException(std::format("FileStorageException: {}", message)) {}
};

#endif
