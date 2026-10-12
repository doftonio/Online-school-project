#pragma once
#include "student.h"
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

    std::string getNumber() const;
    int getCourseYear() const;
    int getMaxCapacity() const;
    const std::vector<Student*>& getStudents() const;

    StudyGroup& operator+=(Student* student);
    StudyGroup& operator-=(int studentId);

    Student* findStudent(int studentId) const;
    void printInfo() const;
};