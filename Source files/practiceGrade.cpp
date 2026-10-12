#include "../Header files/practiceGrade.h"

PracticeGrade::PracticeGrade(int val, const Date& d, int workNum, std::string_view type)
    : Grade(val, d), number(workNum), workType(type) {
}

int PracticeGrade::getNumber() const { return number; }
std::string PracticeGrade::getWorkType() const { return workType; }

std::ostream& operator<<(std::ostream& os, const PracticeGrade& g) {
    os << "[" << g.workType << " ¹" << g.number << ": " << g.value << " á. (" << g.date << ")]";
    return os;
}