#ifndef ENTITY_NOT_FOUND_EXCEPTION_H
#define ENTITY_NOT_FOUND_EXCEPTION_H

#include <string>
#include <format>
#include "appException.h"

class EntityNotFoundException : public AppException {
public:
    explicit EntityNotFoundException(const std::string& message)
        : AppException(std::format("EntityNotFoundException: {}", message)) {}
};

#endif
