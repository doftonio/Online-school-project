#include "../Header files/teacher.h"
#include <iostream>

void Teacher::printInfo() const {
    std::cout << "Teacher [ID: " << id << "] " << getFullName()
              << " | Department: " << department << "\n";
}

std::istream& operator>>(std::istream& is, Teacher& teacher) {
    std::cout << "Enter Teacher ID: ";
    if (!(is >> teacher.id)) {
        return is;
    }
    std::cout << "Enter Last Name: ";
    if (!(is >> teacher.lastName)) {
        return is;
    }
    std::cout << "Enter First Name: ";
    if (!(is >> teacher.firstName)) {
        return is;
    }
    std::cout << "Enter Middle Name: ";
    if (!(is >> teacher.middleName)) {
        return is;
    }
    std::cout << "Enter Department: ";
    is >> teacher.department;
    return is;
}

void inspectTeacherInternals(const Teacher& teacher) {
    std::cout << "[Friend Inspect] Teacher internal ID: " << teacher.id
              << ", Dept: " << teacher.department << "\n";
}
