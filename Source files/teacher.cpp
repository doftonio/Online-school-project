#include "../Header files/teacher.h"
#include <iostream>

Teacher::Teacher(int teacherId, std::string_view first, std::string_view last, std::string_view middle, std::string_view dept)
    : id(teacherId), firstName(first), lastName(last), middleName(middle), department(dept) {
    if (teacherId <= 0) {
        throw InvalidInputDataException("Teacher ID must be positive: provided " + std::to_string(teacherId));
    }
    if (first.empty() || last.empty()) {
        throw InvalidInputDataException("Teacher first name and last name cannot be empty.");
    }
    if (dept.empty()) {
        throw InvalidInputDataException("Teacher department cannot be empty.");
    }
}

int Teacher::calculateAnnualWorkload(int assignedContactHours, double prepMultiplier) const {
    if (assignedContactHours < 0) {
        throw InvalidInputDataException("Assigned contact hours cannot be negative: provided " + std::to_string(assignedContactHours));
    }
    if (prepMultiplier <= 0.0) {
        throw InvalidInputDataException("Preparation multiplier must be positive.");
    }
    return static_cast<int>(assignedContactHours * prepMultiplier);
}

void Teacher::printInfo() const {
    std::cout << "Teacher [ID: " << id << "] " << getFullName()
              << " | Department: " << department << "\n";
}

void inspectTeacherInternals(const Teacher& teacher) {
    std::cout << "[Friend Inspect] Teacher internal ID: " << teacher.id
              << ", Dept: " << teacher.department << "\n";
}

std::ostream& operator<<(std::ostream& os, const Teacher& teacher) {
    os << "Teacher [ID: " << teacher.id << "] " << teacher.getFullName()
       << " (" << teacher.department << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Teacher& teacher) {
    std::cout << "Enter Teacher ID: ";
    if (!(is >> teacher.id)) {
        throw InvalidInputDataException("Invalid input format for teacher ID.");
    }
    if (teacher.id <= 0) {
        throw InvalidInputDataException("Teacher ID must be positive.");
    }
    std::cout << "Enter Last Name: ";
    if (!(is >> teacher.lastName) || teacher.lastName.empty()) {
        throw InvalidInputDataException("Teacher last name cannot be empty.");
    }
    std::cout << "Enter First Name: ";
    if (!(is >> teacher.firstName) || teacher.firstName.empty()) {
        throw InvalidInputDataException("Teacher first name cannot be empty.");
    }
    std::cout << "Enter Middle Name: ";
    if (!(is >> teacher.middleName)) {
        throw InvalidInputDataException("Invalid middle name input.");
    }
    std::cout << "Enter Department: ";
    if (!(is >> teacher.department) || teacher.department.empty()) {
        throw InvalidInputDataException("Teacher department cannot be empty.");
    }
    return is;
}
