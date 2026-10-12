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
    auto operator<=>(const Student& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Student& s) {
        os << "ID: " << s.id
            << " | Name: " << s.getFullName()
            << " | Group: " << (s.groupNumber.empty() ? "N/A" : s.groupNumber)
            << " | Tasks: " << s.completedTasks;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Student& s) {
        std::cout << "Enter student ID: ";
        is >> s.id;
        std::string last{};
        std::string first{};
        std::string middle{};
        std::cout << "Enter last name: ";
        is >> last;
        s.setLastName(last);
        std::cout << "Enter first name: ";
        is >> first;
        s.setFirstName(first);
        std::cout << "Enter middle name ('-' if none): ";
        is >> middle;
        if (middle == "-") middle.clear();
        s.setMiddleName(middle);
        std::cout << "Enter completed tasks count: ";
        is >> s.completedTasks;
        return is;
    }

    friend void inspectStudentInternals(const Student& student);
};