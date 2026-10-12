#pragma once
#include "student.h"
#include <span>
#include <string>
#include <string_view>
#include <vector>

class StudyGroup {
private:
    std::string number{};
    int courseYear{ 1 };
    int maxCapacity{ 30 };
    std::vector<Student*> students{};

public:
    StudyGroup(std::string_view groupNum, int year, int capacity = 30);

    [[nodiscard]] std::string getNumber() const;
    [[nodiscard]] int getCourseYear() const;
    [[nodiscard]] int getMaxCapacity() const;
    [[nodiscard]] std::span<const Student* const> getStudents() const;

    StudyGroup& operator+=(Student* student);
    StudyGroup& operator-=(int studentId);

    [[nodiscard]] Student* findStudent(int studentId);
    [[nodiscard]] const Student* findStudent(int studentId) const;
    void printInfo() const;
};