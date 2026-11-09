#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class AppException : public std::runtime_error {
public:
    explicit AppException(const std::string& message)
        : std::runtime_error(message) {}
};

class InvalidInputDataException : public AppException {
public:
    explicit InvalidInputDataException(const std::string& message)
        : AppException("InvalidInputDataException: " + message) {}
};

class DuplicateEntityException : public AppException {
public:
    explicit DuplicateEntityException(const std::string& message)
        : AppException("DuplicateEntityException: " + message) {}
};

class EntityNotFoundException : public AppException {
public:
    explicit EntityNotFoundException(const std::string& message)
        : AppException("EntityNotFoundException: " + message) {}
};

class CapacityExceededException : public AppException {
public:
    explicit CapacityExceededException(const std::string& message)
        : AppException("CapacityExceededException: " + message) {}
};

class IndexOutOfBoundsException : public AppException {
public:
    explicit IndexOutOfBoundsException(const std::string& message)
        : AppException("IndexOutOfBoundsException: " + message) {}
};

#endif
