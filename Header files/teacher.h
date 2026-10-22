#ifndef TEACHER_H
#define TEACHER_H

#include "person.h"
#include <string>
#include <string_view>

class Teacher : public Person {
private:
    int id{0};
    std::string department;

public:
    Teacher() = default;
    Teacher(int teacherId, std::string_view first, std::string_view last, std::string_view middle, std::string_view dept);

    [[nodiscard]] int getId() const noexcept { return id; }
    [[nodiscard]] const std::string& getDepartment() const noexcept { return department; }

    [[nodiscard]] int calculateAnnualWorkload(int assignedContactHours, double prepMultiplier = 1.25) const noexcept {
        if (assignedContactHours <= 0) return 0;
        return static_cast<int>(assignedContactHours * prepMultiplier);
    }

    void printInfo() const override;
    bool operator==(const Teacher& other) const noexcept { return id == other.id; }
};

#endif // TEACHER_H
