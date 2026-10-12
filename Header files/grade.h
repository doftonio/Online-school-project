#pragma once
#include "date.h"

class Grade {
private:
    int value{ 0 };
    Date date{};

public:
    Grade() = default;
    Grade(int val, const Date& d);
    virtual ~Grade() = default;

    [[nodiscard]] int getValue() const;
    [[nodiscard]] Date getDate() const;
};