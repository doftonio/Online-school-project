#include "../Header files/labGrade.h"

LabGrade::LabGrade(int val, const Date& d, int labNum)
    : Grade(val, d), number(labNum) {
}

int LabGrade::getNumber() const { return number; }

std::ostream& operator<<(std::ostream& os, const LabGrade& g) {
    os << "[Ырс. Й" << g.number << ": " << g.value << " с. (" << g.date << ")]";
    return os;
}