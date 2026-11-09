#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>
#include <format>

class AppException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class InvalidInputDataException : public AppException {
public:
    explicit InvalidInputDataException(const std::string& message)
        : AppException(std::format("InvalidInputDataException: {}", message)) {}
};

class DuplicateEntityException : public AppException {
public:
    explicit DuplicateEntityException(const std::string& message)
        : AppException(std::format("DuplicateEntityException: {}", message)) {}
};

class EntityNotFoundException : public AppException {
public:
    explicit EntityNotFoundException(const std::string& message)
        : AppException(std::format("EntityNotFoundException: {}", message)) {}
};

class CapacityExceededException : public AppException {
public:
    explicit CapacityExceededException(const std::string& message)
        : AppException(std::format("CapacityExceededException: {}", message)) {}
};

class IndexOutOfBoundsException : public AppException {
public:
    explicit IndexOutOfBoundsException(const std::string& message)
        : AppException(std::format("IndexOutOfBoundsException: {}", message)) {}
};

#endif
