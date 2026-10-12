#pragma once
#include "date.h"

class Grade {
protected:
    int value{ 0 };
    Date date{};

public:
    Grade() = default;
    Grade(int val, const Date& d);
    virtual ~Grade() = default;

    int getValue() const;
    Date getDate() const;
};