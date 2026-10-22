#ifndef DATE_H
#define DATE_H

#include <compare>

class Date {
private:
    int day{1};
    int month{1};
    int year{2026};

public:
    Date() = default;
    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    int getDay() const noexcept { return day; }
    int getMonth() const noexcept { return month; }
    int getYear() const noexcept { return year; }

    bool operator==(const Date& other) const noexcept = default;
    auto operator<=>(const Date& other) const noexcept = default;
};

#endif // DATE_H
