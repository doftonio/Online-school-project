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
    virtual ~Grade() = default;

    Grade(Grade&&) noexcept = default;
    Grade& operator=(Grade&&) noexcept = default;
    Grade(const Grade&) = default;
    Grade& operator=(const Grade&) = default;

    int getValue() const noexcept { return value; }
    Date getDate() const noexcept { return date; }
    int getWorkNumber() const noexcept { return workNumber; }
    std::string_view getTopicOrType() const noexcept { return topicOrType; }
};

class LabGrade : public Grade {
public:
    LabGrade() = default;
    LabGrade(int val, const Date& d, int num = 0)
        : Grade(val, d, num, "Lab") {}
};

class PracticeGrade : public Grade {
public:
    PracticeGrade() = default;
    PracticeGrade(int val, const Date& d, int num = 0, std::string_view type = "")
        : Grade(val, d, num, type) {}
};

#endif // GRADE_H
