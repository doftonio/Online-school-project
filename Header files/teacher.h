#pragma once
#include "person.h"
#include <string_view>

class Teacher : public Person {
private:
    int id{ 0 };
    std::string department{};

public:
    Teacher() = default;
    Teacher(int teacherId, std::string_view first, std::string_view last, std::string_view middle, std::string_view dept);

    int getId() const;
    std::string getDepartment() const;

    void printInfo() const override;
    bool operator==(const Teacher& other) const;
};