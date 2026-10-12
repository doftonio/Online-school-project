#pragma once
#include <stdexcept>

class AppException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class EntityNotFoundException : public AppException {
public:
    using AppException::AppException;
};

class DuplicateEntityException : public AppException {
public:
    using AppException::AppException;
};

class CapacityExceededException : public AppException {
public:
    using AppException::AppException;
};

class InvalidOperationException : public AppException {
public:
    using AppException::AppException;
};