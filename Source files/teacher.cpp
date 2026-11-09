#include "../Header files/teacher.h"
#include <iostream>
#include <format>

Teacher::Teacher(int teacherId, std::string_view first, std::string_view last, std::string_view middle, std::string_view dept)
    : id(teacherId), firstName(first), lastName(last), middleName(middle), department(dept) {
    if (teacherId <= 0) {
        throw InvalidInputDataException(std::format("Teacher ID must be positive: provided {}", teacherId));
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
        throw InvalidInputDataException(std::format("Assigned contact hours cannot be negative: provided {}", assignedContactHours));
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
