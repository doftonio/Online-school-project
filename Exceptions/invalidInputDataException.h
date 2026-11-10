#ifndef INVALID_INPUT_DATA_EXCEPTION_H
#define INVALID_INPUT_DATA_EXCEPTION_H

#include <string>
#include <format>
#include "appException.h"

class InvalidInputDataException : public AppException {
public:
    explicit InvalidInputDataException(const std::string& message)
        : AppException(std::format("InvalidInputDataException: {}", message)) {}
};

#endif
