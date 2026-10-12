#pragma once
#include <stdexcept>
#include <string>

class AppException : public std::runtime_error {
public:
    explicit AppException(const std::string& message) : std::runtime_error(message) {}
};

class EntityNotFoundException : public AppException {
public:
    explicit EntityNotFoundException(const std::string& message) : AppException(message) {}
};

class DuplicateEntityException : public AppException {
public:
    explicit DuplicateEntityException(const std::string& message) : AppException(message) {}
};

class CapacityExceededException : public AppException {
public:
    explicit CapacityExceededException(const std::string& message) : AppException(message) {}
};

class InvalidOperationException : public AppException {
public:
    explicit InvalidOperationException(const std::string& message) : AppException(message) {}
};