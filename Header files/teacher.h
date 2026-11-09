#ifndef TEACHER_H
#define TEACHER_H

#include <string>
#include <string_view>
#include <compare>
#include <iostream>
#include <format>
#include "exceptions.h"

class Teacher {
private:
    int id{0};
    std::string firstName;
    std::string lastName;
    std::string middleName;
    std::string department;

public:
    Teacher() = default;
    Teacher(int teacherId, std::string_view first, std::string_view last, std::string_view middle, std::string_view dept);

    int getId() const noexcept { return id; }
    const std::string& getFirstName() const noexcept { return firstName; }
    const std::string& getLastName() const noexcept { return lastName; }
    const std::string& getMiddleName() const noexcept { return middleName; }
    const std::string& getDepartment() const noexcept { return department; }

    std::string getFullName() const {
        return std::format("{} {} {}", lastName, firstName, middleName);
    }

    int calculateAnnualWorkload(int assignedContactHours, double prepMultiplier = 1.25) const;

    void printInfo() const;

    bool operator==(const Teacher& other) const noexcept { return id == other.id; }
    auto operator<=>(const Teacher& other) const noexcept { return id <=> other.id; }

    friend std::ostream& operator<<(std::ostream& os, const Teacher& teacher) {
        os << std::format("Teacher [ID: {}] {} ({})", teacher.id, teacher.getFullName(), teacher.department);
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Teacher& teacher) {
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

    friend void inspectTeacherInternals(const Teacher& teacher);
};

void inspectTeacherInternals(const Teacher& teacher);

#endif
