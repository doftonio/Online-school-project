#include "../Header files/labGrade.h"

LabGrade::LabGrade(int val, const Date& d, int labNum)
    : Grade(val, d), number(labNum) {
}

int LabGrade::getNumber() const { return number; }