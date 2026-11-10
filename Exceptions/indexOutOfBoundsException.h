#ifndef INDEX_OUT_OF_BOUNDS_EXCEPTION_H
#define INDEX_OUT_OF_BOUNDS_EXCEPTION_H

#include <string>
#include <format>
#include "appException.h"

class IndexOutOfBoundsException : public AppException {
public:
    explicit IndexOutOfBoundsException(const std::string& message)
        : AppException(std::format("IndexOutOfBoundsException: {}", message)) {}
};

#endif
