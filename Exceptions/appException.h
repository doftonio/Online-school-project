#ifndef APP_EXCEPTION_H
#define APP_EXCEPTION_H

#include <stdexcept>
#include <string>

class AppException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

#endif
