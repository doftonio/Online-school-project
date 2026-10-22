#ifndef GRADE_H
#define GRADE_H

#include <string>
#include <string_view>
#include "date.h"

class Grade {
private:
    int value{0};
    Date date;
    int workNumber{0};
    std::string topicOrType;

public:
    Grade() = default;
    Grade(int val, const Date& d, int num = 0, std::string_view topic = "")
        : value(val), date(d), workNumber(num), topicOrType(topic) {}

    [[nodiscard]] int getValue() const noexcept { return value; }
    [[nodiscard]] Date getDate() const noexcept { return date; }
    [[nodiscard]] int getWorkNumber() const noexcept { return workNumber; }
    [[nodiscard]] std::string_view getTopicOrType() const noexcept { return topicOrType; }
};

#endif // GRADE_H
