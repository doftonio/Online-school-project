#ifndef CAPACITY_EXCEEDED_EXCEPTION_H
#define CAPACITY_EXCEEDED_EXCEPTION_H

#include <string>
#include <format>
#include "appException.h"

class CapacityExceededException : public AppException {
public:
    explicit CapacityExceededException(const std::string& message)
        : AppException(std::format("CapacityExceededException: {}", message)) {}
};

#endif
