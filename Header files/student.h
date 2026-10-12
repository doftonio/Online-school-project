#pragma once
#include "person.h"
#include <compare>
#include <iostream>

class Student : public Person {
private:
    int id{ 0 };
    std::string groupNumber{};
    int completedTasks{ 0 };

public:
    Student() = default;
    Student(int studentId, std::string_view first, std::string_view last, std::string_view middle = "", int tasks = 0);

    int getId() const;
    std::string getGroupNumber() const;
    int getCompletedTasks() const;

    void setGroupNumber(std::string_view group);
    void completeTask();
    void setCompletedTasks(int tasks);

    void printInfo() const override;

    bool operator==(const Student& other) const;
    bool operator!=(const Student& other) const;

    bool operator<(const Student& other) const;
    bool operator>(const Student& other) const;
    bool operator<=(const Student& other) const;
    bool operator>=(const Student& other) const;
    auto operator<=>(const Student& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Student& s);
    friend std::istream& operator>>(std::istream& is, Student& s);
    friend void inspectStudentInternals(const Student& student);
};