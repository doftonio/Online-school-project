#pragma once
#include <iostream>

class Date {
private:
    int day{ 1 };
    int month{ 1 };
    int year{ 2026 };

public:
    Date() = default;
    Date(int d, int m, int y);

    int getDay() const;
    int getMonth() const;
    int getYear() const;

    bool operator==(const Date& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Date& d);
};