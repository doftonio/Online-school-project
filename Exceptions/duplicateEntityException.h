#ifndef DUPLICATE_ENTITY_EXCEPTION_H
#define DUPLICATE_ENTITY_EXCEPTION_H

#include <string>
#include <format>
#include "appException.h"

class DuplicateEntityException : public AppException {
public:
    explicit DuplicateEntityException(const std::string& message)
        : AppException(std::format("DuplicateEntityException: {}", message)) {}
};

#endif
