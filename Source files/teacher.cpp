#include "../Header files/teacher.h"
#include <iostream>

void Teacher::printInfo() const {
    std::cout << "Teacher [ID: " << id << "] " << getFullName()
              << " | Department: " << department << "\n";
}

void inspectTeacherInternals(const Teacher& teacher) {
    std::cout << "[Friend Inspect] Teacher internal ID: " << teacher.id
              << ", Dept: " << teacher.department << "\n";
}
