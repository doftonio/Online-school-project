#include "../Header files/date.h"

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {}

int Date::getDay() const { return day; }
int Date::getMonth() const { return month; }
int Date::getYear() const { return year; }

bool Date::operator==(const Date& other) const {
    return day == other.day && month == other.month && year == other.year;
}

std::ostream& operator<<(std::ostream& os, const Date& d) {
    os << (d.day < 10 ? "0" : "") << d.day << "."
        << (d.month < 10 ? "0" : "") << d.month << "."
        << d.year;
    return os;
}