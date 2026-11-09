#ifndef TEACHER_H
#define TEACHER_H

#include <string>
#include <string_view>
#include <compare>
#include <iostream>
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
        return lastName + " " + firstName + " " + middleName;
    }

    int calculateAnnualWorkload(int assignedContactHours, double prepMultiplier = 1.25) const;

    void printInfo() const;

    bool operator==(const Teacher& other) const noexcept { return id == other.id; }
    auto operator<=>(const Teacher& other) const noexcept { return id <=> other.id; }

    friend std::ostream& operator<<(std::ostream& os, const Teacher& teacher);
    friend std::istream& operator>>(std::istream& is, Teacher& teacher);

    friend void inspectTeacherInternals(const Teacher& teacher);
};

void inspectTeacherInternals(const Teacher& teacher);

#endif
