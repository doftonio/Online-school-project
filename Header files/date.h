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

    [[nodiscard]] int getDay() const;
    [[nodiscard]] int getMonth() const;
    [[nodiscard]] int getYear() const;

    bool operator==(const Date& other) const = default;

    friend std::ostream& operator<<(std::ostream& os, const Date& d) {
        os << (d.day < 10 ? "0" : "") << d.day << "."
            << (d.month < 10 ? "0" : "") << d.month << "."
            << d.year;
        return os;
    }
};